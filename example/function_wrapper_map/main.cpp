#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "mygameserver.h"
#include "myuser.h"
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Worker worker(4);

    MyGameServer ws;
    QObject::connect(&ws, &WebSocketServer::OnCreatedWebSocket, &worker, &Worker::MoveToThread);
    ws.Bind<MyUser>(R"##(\/123)##").Listen(33333);

    qDebug() << QThread::currentThreadId() << __FUNCTION__;

    return a.exec();
}
