#include "zmqirclog.h"
#include <travlrsutils/filesystem.h>
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDate>
#include <QDateTime>
#include <QProcess>
#include <QDebug>

ZmqIrcLog::ZmqIrcLog(QObject *parent)
    : QObject(parent)
{
    m_logDirPath = qApp->arguments().at(1);
    m_repoDirPath = qApp->arguments().at(2);
    m_logFilePath = m_logDirPath + "/freenode_#zeromq.log";
    m_zmqLogDirPath = m_logDirPath + "/zeromq";
    m_rstDirPath = m_repoDirPath + "/rst";
    m_rstSrcDirPath = m_rstDirPath + "/source";
    m_rstHtmlDirPath = m_rstDirPath + "/build/html";
    m_tmpHtmlDirPath = QString("/tmp/rst/html");
    m_years << "2010" << "2011" << "2012";
}


void ZmqIrcLog::run()
{
    moveZmqLogToMonthly();
    moveMonthlyToRstSrc();
    runSphinx();
    moveHtmlToTmp();
    checkoutGhPages();
    moveHtmlToGhPages();
//    pushHtmlToGitHub();
}

void ZmqIrcLog::moveZmqLogToMonthly()
{
    QFile logFile(m_logFilePath);
    logFile.open(QIODevice::ReadOnly);
    QStringList lines = QString(logFile.readAll()).split("\n");
    logFile.close();
    // rename the orig log file
    QDateTime dt = QDateTime::currentDateTime();
    QString dtString = dt.toString();
    logFile.rename(logFile.fileName() + "-" + dtString);
    QString comparativeMonth = QString();
    QString currentMonth = QString();
    QString year = QString();

    // get comparativeMonth
    foreach (QString line, lines) {
        comparativeMonth = extractMonthFromLine(line);
        if (!comparativeMonth.isNull())
            break;
    }

    QStringList monthLines;

    // parse the lines
//    QString year;
//    QString month;
    foreach (QString line, lines) {
        currentMonth = extractMonthFromLine(line);
        QString tmpYear = extractYearFromLine(line);
        if (!tmpYear.isNull())
            year = tmpYear;
        if (currentMonth.isNull() || currentMonth == comparativeMonth)
            monthLines.append(line);
        else if (!currentMonth.isNull() && currentMonth != comparativeMonth) {
            currentMonth = comparativeMonth;
            QString month = comparativeMonth;
            // see if there is alread a file for this year-month
            QString fileName = year + "-" + month;
            m_alteredFileNames.append(fileName);
            QFile monthFile(m_zmqLogDirPath + "/" + fileName);
            if (!monthFile.exists()) {
                // create a new month file
                monthFile.open(QIODevice::WriteOnly);
                monthFile.write(monthLines.join("\n").toLocal8Bit());
                monthFile.close();
            }
            else {
                // append to existing month file
                monthFile.open(QIODevice::ReadOnly);
                QStringList oldLines = QString(monthFile.readAll()).split("\n");
                monthFile.close();
                monthFile.remove();
                foreach (QString line, monthLines)
                    oldLines.append(line);
                monthFile.open(QIODevice::WriteOnly);
                monthFile.write(oldLines.join("\n").toLocal8Bit());
                monthFile.close();
            }
        }
    }
    // we need to do this one more time for that last set of month lines
    QString month = comparativeMonth;
    // see if there is alread a file for this year-month
    QString fileName = year + "-" + month;
    m_alteredFileNames.append(fileName);
    QFile monthFile(m_zmqLogDirPath + "/" + fileName);
    if (!monthFile.exists()) {
        // create a new month file
        monthFile.open(QIODevice::WriteOnly);
        monthFile.write(monthLines.join("\n").toLocal8Bit());
        monthFile.close();
    }
    else {
        // append to existing month file
        monthFile.open(QIODevice::ReadOnly);
        QStringList oldLines = QString(monthFile.readAll()).split("\n");
        monthFile.close();
        monthFile.remove();
        foreach (QString line, monthLines)
            oldLines.append(line);
        monthFile.open(QIODevice::WriteOnly);
        monthFile.write(oldLines.join("\n").toLocal8Bit());
        monthFile.close();
    }
}

void ZmqIrcLog::moveMonthlyToRstSrc()
{
    QDir rstSrcDir(m_rstSrcDirPath);
    QStringList rstFileNames;
    QStringList nameFilters;
    nameFilters << "*.rst";
    QDir::Filters filters = QDir::Files;
    rstFileNames = rstSrcDir.entryList(nameFilters, filters);
    foreach (QString alteredFileName, m_alteredFileNames) {
        if (!rstFileNames.contains(alteredFileName)) {
            // just add the new file
            QFile monthlyLogFile(m_zmqLogDirPath + "/" + alteredFileName);
            monthlyLogFile.open(QIODevice::ReadOnly);
            QStringList lines = QString(monthlyLogFile.readAll()).split("\n");
            monthlyLogFile.close();
            convertLogLinesToRstLines(lines);
            addHeaderToRstFile(lines, alteredFileName);
            QFile newRstFile(m_rstSrcDirPath + "/" + alteredFileName);
            newRstFile.open(QIODevice::WriteOnly);
            newRstFile.write(lines.join("\n").toLocal8Bit());
            newRstFile.close();
            // add new Rst file to toc list
            m_newTocTitles.append(newRstFile.fileName().split("/").last().split(".").first());
        }
        else {
            // append the new lines to the old rst file
            QFile monthlyLogFile(m_zmqLogDirPath + "/" + alteredFileName);
            monthlyLogFile.open(QIODevice::ReadOnly);
            QStringList logLines = QString(monthlyLogFile.readAll()).split("\n");
            monthlyLogFile.close();
            convertLogLinesToRstLines(logLines);
            QFile rstFile(m_rstSrcDirPath + "/" + alteredFileName);
            QStringList rstLines = QString(rstFile.readAll()).split("\n");
            rstLines += logLines;
            rstFile.remove();
            rstFile.open(QIODevice::WriteOnly);
            rstFile.write(rstLines.join("\n").toLocal8Bit());
            rstFile.close();
        }
    }
    qDebug() << "moveZmqLogToMonthly() completed..";
}

void ZmqIrcLog::addTocToRstIndexFile()
{
    if (m_newTocTitles.isEmpty())
        return;
    QFile idxFile(m_rstSrcDirPath + "/index.rst");
    idxFile.open(QIODevice::ReadOnly);
    QStringList lines = QString(idxFile.readAll()).split("\n");
    idxFile.close();
    QStringList newLines;
    State state = NONE;

    foreach (QString line, lines) {

        if ((state == NONE && (!line.contains(QString(":maxdepth")))))
            newLines.append(line);

        if ((state == NONE) && (line.contains(QString(":maxdepth:")))) {
            state = MAXDEPTH;
            newLines.append(line);
        }
        else if ((state == MAXDEPTH) && (line == QString(""))) {
            state = MAXDEPTH_PLUS_ONE;
            newLines.append(line);
        }
        else if ((state == MAXDEPTH_PLUS_ONE) && (line.contains(QString("Indices")))) {
            foreach (QString tocTitle, m_newTocTitles)
                newLines.append(tocTitle.prepend("   "));
            newLines.append("\n");
            newLines.append(line);
            state = INDICES;
        }
        else if ((state == MAXDEPTH_PLUS_ONE) && (!extractMonthFromLine(line).isNull()))
            state = TOC;
        else if ((state == TOC) && (line == QString(""))) {
            foreach (QString tocTitle, m_newTocTitles)
                newLines.append(tocTitle.prepend("   "));
            newLines.append(line);
            state = INSERTED;
        }
        else if ((state == INDICES) || (state == INSERTED))
            newLines.append(line);
    }
    idxFile.open(QIODevice::WriteOnly);
    idxFile.write(newLines.join("\n").toLocal8Bit());
    idxFile.close();

    qDebug() << "addTocToRstIndexFile() completed..";
}

void ZmqIrcLog::runSphinx()
{
    QProcess* proc = new QProcess();
    QString prog("make");
    QStringList args(QString("html"));
    proc->setWorkingDirectory(m_rstDirPath);
    proc->start(prog, args);
    proc->waitForFinished(-1);

    qDebug() << "runSphinx() completed..";
}

void ZmqIrcLog::moveHtmlToTmp()
{
    travlr::FileSystem fs;
    QDir tmpHtmlDir(m_tmpHtmlDirPath);
    if (tmpHtmlDir.exists())
        fs.cleanTheDirectory(m_tmpHtmlDirPath);
    else
        tmpHtmlDir.mkpath(m_tmpHtmlDirPath);
    fs.moveDirectoryContents(m_rstHtmlDirPath, m_tmpHtmlDirPath);

    qDebug() << "moveHtmlToTmp() completed..";
}

void ZmqIrcLog::checkoutGhPages()
{
    QStringList args;
    // first create the git instance
    m_git = new travlr::Git(m_repoDirPath, this);
    m_gitProc = m_git->process();
    connect(m_gitProc, SIGNAL(readyReadStandardError()), this, SLOT(slotReadStdErr()));
    connect(m_gitProc, SIGNAL(readyReadStandardOutput()), this, SLOT(slotReadStdOut()));

    // clean up the repo by pushing master
    args << ".";
    m_git->add(args);
    args.clear();
    args << "-am" << "automated update";
    m_git->commit(args);
    args.clear();
    args << "origin" << "master";
    m_git->push(args);

    // checkout gh-pages
    args.clear();
    args << "gh-pages";
    m_git->checkout(args);

    qDebug() << "checkoutGhPages() completed..";
}

void ZmqIrcLog::moveHtmlToGhPages()
{
    travlr::FileSystem fs;
    QString readMeFilePath(m_repoDirPath + "/README.rst");
    QString gitFilePath(m_repoDirPath + "/.git");
    QStringList exceptioins;
    exceptioins << readMeFilePath << gitFilePath;
    fs.cleanTheDirectory(m_repoDirPath, exceptioins);
    fs.moveDirectoryContents(m_tmpHtmlDirPath, m_repoDirPath);

    qDebug() << "moveHtmlToGhPages() completed..";
}

void ZmqIrcLog::pushGhPagesToGitHub()
{
    QStringList args;
    args << ".";
    m_git->add(args);
    args.clear();
    args << "-am" << "automated update";
    m_git->commit(args);
    args.clear();
    args << "origin" << "gh-pages";
    m_git->push(args);

    qDebug() << "pushGhPagesToGitHub() completed..";
}






//
// helper methods
//

/// returns the month contained in the line or NULL if nonexistent.
QString ZmqIrcLog::extractMonthFromLine(const QString & line)
{
    QString month;
    for (int i=1;i<13;++i) {
        month = QDate::longMonthName(i);
        if (line.contains(month))
            return month;
    }
    return QString();
}

QString ZmqIrcLog::extractYearFromLine(const QString & line)
{
    foreach (QString year, m_years) {
        if (line.contains(year))
            return year;
    }
    return QString();
}

void ZmqIrcLog::convertLogLinesToRstLines(QStringList &lines)
{
    // make lines rst literals
    QStringList newLines;
    foreach (QString line, lines)
        newLines.append(line.prepend("| "));
    lines = newLines;
}

void ZmqIrcLog::addHeaderToRstFile(QStringList &lines, const QString &fileName)
{
    lines.prepend("===============\n");
    lines.prepend(fileName.split(".").at(0));
    lines.prepend("===============");
}




// slots

void ZmqIrcLog::slotReadStdErr()
{
    qDebug() << m_gitProc->readAllStandardError();
}

void ZmqIrcLog::slotReadStdOut()
{
    qDebug() << m_gitProc->readAllStandardOutput();
}







































































