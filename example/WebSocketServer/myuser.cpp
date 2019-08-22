#include "myuser.h"

#include <QDebug>

MyUser::MyUser(QWebSocket *qweb_socket, QObject *parent) : WebSocket (qweb_socket, parent)
{
    qDebug() << __FUNCTION__;
}

void MyUser::OnRelease()
{
    qDebug() <<  __FUNCTION__;
}

void MyUser::OnReceiveMessage(const QString &text)
{
    qDebug() << __FUNCTION__ << text;
    emit SendMessage(text);
}
