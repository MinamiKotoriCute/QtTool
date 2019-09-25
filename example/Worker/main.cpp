#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QTimer>

#include "mygameserver.h"
#include "myuser.h"
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    /// test 1
//    Worker worker(4);

//    MyGameServer ws;
//    QObject::connect(&ws, &WebSocketServer::OnCreatedWebSocket, &worker, &Worker::MoveToThread);
//    ws.Bind<MyUser>(R"##(\/123)##").Listen(33333);

//    qDebug() << QThread::currentThreadId() << __FUNCTION__;
    /// test 1 end

    /// test 2
    qDebug() << QThread::currentThreadId() << __FUNCTION__;
    int thread_number = 4;
    Worker worker(thread_number);
    for(int i=0;i<thread_number;++i) {
        QObject *o = new QObject;
        QObject::connect(o, &QObject::destroyed, []{qDebug() << QThread::currentThreadId() << "QObject::destroyed";});
        worker.MoveToSpecificThread(i, o);
        QTimer::singleShot(0, o, [o]{
            qDebug() << QThread::currentThreadId() << "QObject::start";
            QObject::connect(QThread::currentThread(), &QThread::finished, o, &QObject::deleteLater);
        });
    }

    QTimer::singleShot(3000, &worker, [&worker]{
        qDebug() << "stoping";
        worker.Stop();
        qDebug() << "stoped";
    });
    /// test 2 emd

    return a.exec();
}
