#include "websocket.h"

#include <QWebSocket>
#include <QTimer>

WebSocket::WebSocket(QWebSocket *qweb_socket, QObject *parent) :
    QObject(parent),
    qweb_socket_(qweb_socket)
{
    connect(this, &WebSocket::SendMessage, qweb_socket_, &QWebSocket::sendTextMessage);
    connect(qweb_socket_, &QWebSocket::textMessageReceived, this, &WebSocket::OnReceiveMessage);
    connect(qweb_socket_, &QWebSocket::disconnected, this, &WebSocket::OnRelease);
    connect(qweb_socket_, &QWebSocket::disconnected, this, &WebSocket::deleteLater);
}

WebSocket::~WebSocket()
{
    qweb_socket_->close();
    qweb_socket_->deleteLater();
}
