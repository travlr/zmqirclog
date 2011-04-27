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
    addTocToRstIndexFile();
    runSphinx();
    moveHtmlToTmp();
    checkoutGhPages();
    moveHtmlToGhPages();
    pushGhPagesToGitHub();
    qApp->exit(0);
}

void ZmqIrcLog::moveZmqLogToMonthly()
{
    QFile logFile(m_logFilePath);
    logFile.open(QIODevice::ReadOnly);
    QStringList lines = QString(logFile.readAll()).split("\n");
    logFile.close();
    // rename the orig log file
    QDateTime dt = QDateTime::currentDateTime();
    QString dtString = dt.toString().replace(" ", "_");
    if (logFile.copy(m_logFilePath + "/zeromq" + "-" + dtString + ".log"))
        QFile::remove(m_logFilePath);
    QString comparativeMonth = QString();
    QString currentMonth = QString();
    QString year = QString();
    QString month = QString();

    // get comparativeMonth
    foreach (QString line, lines) {
        comparativeMonth = extractMonthFromLine(line, extractYearFromLine(line));
        if (!comparativeMonth.isNull()) {
            qDebug() << "The comparative month is: " << comparativeMonth;
            break;
        }
    }

    QStringList monthLines;

    // parse the lines
    foreach (QString line, lines) {
        if ((line.contains("] Join"))
                || (line.contains("] Quit"))
                || (line.contains("] Topic"))
                || (line.contains("] Created"))
                || (line.contains("] Mode"))
                || (line.contains("] Part"))
                || (line.contains("] Nick"))
                || (line.contains("*** Logfile"))
                || (line.contains("*** on"))
                || (line == QString("")))
            continue;
        QString tmpYear = extractYearFromLine(line);
        currentMonth = extractMonthFromLine(line, extractYearFromLine(line));

//        qDebug() << comparativeMonth << currentMonth << year;
        if (tmpYear.isNull() || currentMonth.isNull() || currentMonth == comparativeMonth) {
            monthLines.append(line);
            continue;
        }
        year = tmpYear;
        if (currentMonth != comparativeMonth) {
            qDebug() << "Time to change a file. The comparative month is: " << comparativeMonth << " and the current month is: " << currentMonth;
            month = comparativeMonth;
            // see if there is alread a file for this year-month
            QString fileName = year + "-" + month + ".log";
            if (m_alteredFileNames.contains(fileName.split(".").first()))
                continue;
            m_alteredFileNames.append(fileName.split(".").first());
            QFile monthFile(m_zmqLogDirPath + "/" + fileName);

            if (!monthFile.exists()) {
                // create a new month file
                monthFile.open(QIODevice::WriteOnly);
                monthFile.write(monthLines.join("\n").toLocal8Bit());
                monthFile.close();
                qDebug() << "Created a new zeromq log monthly file: " << monthFile.fileName();
            }
            else {
                // append to existing month file
                monthFile.open(QIODevice::ReadOnly);
                QStringList oldLines = QString(monthFile.readAll()).split("\n");
                monthFile.close();
                monthFile.remove();
                oldLines += monthLines;
                monthFile.open(QIODevice::WriteOnly);
                monthFile.write(oldLines.join("\n").toLocal8Bit());
                monthFile.close();
                qDebug() << "Appended log lines to an already existing zeromq monthly log file: " << monthFile.fileName();
            }
            comparativeMonth = currentMonth;
            monthLines.clear();
        }
    }
    // we need to do this one more time for that last set of month lines
    month = comparativeMonth;
    // see if there is alread a file for this year-month
    QString fileName = year + "-" + month + ".log";
    m_alteredFileNames.append(fileName.split(".").first());
    QFile monthFile(m_zmqLogDirPath + "/" + fileName);
    if (!monthFile.exists()) {
        // create a new month file
        monthFile.open(QIODevice::WriteOnly);
        monthFile.write(monthLines.join("\n").toLocal8Bit());
        monthFile.close();
        qDebug() << "Created a new zeromq log monthly file: " << monthFile.fileName();
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
        qDebug() << "Appended log lines to an already existing zeromq monthly log file: " << monthFile.fileName();
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
    qDebug() << m_alteredFileNames;
    qDebug() << rstFileNames;
    foreach (QString alteredFileName, m_alteredFileNames) {
        if (!rstFileNames.contains(alteredFileName + ".rst")) {
            // just add the new file
            QFile monthlyLogFile(m_zmqLogDirPath + "/" + alteredFileName + ".log");
            monthlyLogFile.open(QIODevice::ReadOnly);
            QStringList lines = QString(monthlyLogFile.readAll()).split("\n");
            monthlyLogFile.close();
            convertLogLinesToRstLines(lines);
//            addHeaderToRstFile(lines, alteredFileName);
            lines.prepend("===============\n");
            lines.prepend(alteredFileName);
            lines.prepend("===============");
            QFile newRstFile(m_rstSrcDirPath + "/" + alteredFileName + ".rst");
            newRstFile.open(QIODevice::WriteOnly);
            newRstFile.write(lines.join("\n").toLocal8Bit());
            newRstFile.close();
            // add new Rst file to toc list
            if (!m_newTocTitles.contains(alteredFileName))
                m_newTocTitles.append(alteredFileName);
        }
        else {
            // append the new lines to the old rst file
            QFile monthlyLogFile(m_zmqLogDirPath + "/" + alteredFileName + ".log");
            monthlyLogFile.open(QIODevice::ReadOnly);
            QStringList logLines = QString(monthlyLogFile.readAll()).split("\n");
            monthlyLogFile.close();
            convertLogLinesToRstLines(logLines);
            QFile rstFile(m_rstSrcDirPath + "/" + alteredFileName + ".rst");
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
        else if ((state == MAXDEPTH_PLUS_ONE) && (!extractMonthFromLine(line, extractYearFromLine(line)).isNull()))
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
    qDebug() << "Starting runSphinx()..";
    m_proc = new QProcess();
    m_proc->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_proc, SIGNAL(readyRead()), this, SLOT(slotReadStdErrAndOut()));
    QString prog("make");
    QStringList args(QString("html"));
    m_proc->setWorkingDirectory(m_rstDirPath);
    m_proc->start(prog, args);
    m_proc->waitForFinished(-1);

    if (m_proc) {
        disconnect(m_proc, SIGNAL(readyRead()), this, SLOT(slotReadStdErrAndOut()));
        delete m_proc;
        m_proc = 0;
    }

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
    fs.copyDirectoryContents(m_rstHtmlDirPath, m_tmpHtmlDirPath);
    qDebug() << "moveHtmlToTmp() completed..";
}

void ZmqIrcLog::checkoutGhPages()
{
    QStringList args;
    // first create the git instance
    m_git = new travlr::Git(m_repoDirPath, this);
    m_proc = m_git->process();
    m_proc->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_proc, SIGNAL(readyRead()), this, SLOT(slotReadStdErrAndOut()));


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
    fs.copyDirectoryContents(m_tmpHtmlDirPath, m_repoDirPath);

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
    if (QFile::exists(m_repoDirPath + "/zmqirclog.pro.user"))
        QFile::remove(m_repoDirPath + "/zmqirclog.pro.user");
    args.clear();
    args << "master";
    m_git->checkout(args);

    if (m_proc) {
        delete m_proc;
        m_proc = 0;
        disconnect(m_proc, SIGNAL(readyRead()), this, SLOT(slotReadStdErrAndOut()));
    }

    qDebug() << "pushGhPagesToGitHub() completed..";
}






//
// helper methods
//

/// returns the month contained in the line or NULL if nonexistent.
QString ZmqIrcLog::extractMonthFromLine(const QString & line, const QString & year)
{
    QString month;
    for (int i=1;i<13;++i) {
        month = QDate::longMonthName(i);
        if (line.contains(month + " " + year))
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
    lines.prepend(fileName);
    lines.prepend("===============");
}




// slots

void ZmqIrcLog::slotReadStdErrAndOut()
{
    qDebug() << m_proc->readAllStandardOutput();
}








































































