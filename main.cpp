#include <zmqirclog.h>
#include <cstdio>
#include <cstdlib>
#include <QtCore/QCoreApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != 3) {
        fprintf(stderr, "\nUsage: %s <logDirPath> <repoDirPath>\n\n", argv[0]);
        exit(1);
    }
    ZmqIrcLog zil;
    QTimer::singleShot(0, &zil, SLOT(run()));
    return a.exec();
}
