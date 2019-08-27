#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "web_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WebServer ws;
    ws.RegistRestfulApi<>();

    return a.exec();
}
