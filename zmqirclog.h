#ifndef ZMQIRCLOG_H
#define ZMQIRCLOG_H

#include <travlrsutils/git.h>
#include <QObject>
#include <QString>
#include <QStringList>


class ZmqIrcLog : public QObject
{
    Q_OBJECT

public:
    explicit ZmqIrcLog(QObject *parent = 0);
    void run();


private slots:

private:
    // types
    enum State { NONE, MAXDEPTH, MAXDEPTH_PLUS_ONE, TOC, INSERTED, INDICES };

    // methods
    void moveZmqLogToMonthly();
    void moveMonthlyToRstSrc();
    void addTocToRstIndexFile();
    void runSphinx();
    void moveHtmlToTmp();
    void checkoutGhPages();
    void moveHtmlToGhPages();
    void pushGhPagesToGitHub();

    // helper methods
    QString extractMonthFromLine(const QString & line);
    QString extractYearFromLine(const QString & line);
    void convertLogLinesToRstLines(QStringList & lines);
    void addHeaderToRstFile(QStringList & lines, const QString & fileName);


    // variables
    QString m_logDirPath;
    QString m_zmqLogDirPath;
    QString m_repoDirPath;
    QString m_rstDirPath;
    QString m_rstSrcDirPath;
    QString m_rstHtmlDirPath;
    QString m_logFilePath;
    QString m_tmpHtmlDirPath;

    QStringList m_years;
    QStringList m_alteredFileNames;
    QStringList m_newTocTitles;
    State m_state;
    travlr::Git* m_git;
};

#endif // ZMQIRCLOG_H
