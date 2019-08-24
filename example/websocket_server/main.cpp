#include <QCoreApplication>
#include <QDebug>

#include <QTimer>
#include "mygameserver.h"
#include "myuser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyGameServer ws;
    ws.Bind<MyUser>(R"##(\/123)##").Listen(33333);

    return a.exec();
}
