#include "myuser.h"

#include <QDebug>
#include <QThread>

MyUser::MyUser(QWebSocket *qweb_socket, QObject *parent) : WebSocket (qweb_socket, parent)
{
    qDebug() << QThread::currentThreadId() << __FUNCTION__;
}

void MyUser::OnRelease()
{
    qDebug() << QThread::currentThreadId() << __FUNCTION__;
}

void MyUser::OnReceiveMessage(const QString &text)
{
    qDebug() << QThread::currentThreadId() << __FUNCTION__;
    emit SendMessage(text);
}
