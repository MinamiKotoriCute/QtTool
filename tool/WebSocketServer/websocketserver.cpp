#include "websocketserver.h"

#include <QRegularExpression>
#include <QWebSocketServer>
#include <QWebSocket>

#include "websocket.h"

WebSocketServer::WebSocketServer(QObject *parent) :
    QObject(parent),
    web_socket_server_(new QWebSocketServer("WebSocketServer", QWebSocketServer::NonSecureMode, this))
{
    connect(web_socket_server_, &QWebSocketServer::newConnection,
            this, &WebSocketServer::OnNewConnection);
}

WebSocketServer::~WebSocketServer()
{
    web_socket_server_->close();
}

bool WebSocketServer::Listen(quint16 port, const QHostAddress &address)
{
    return web_socket_server_->listen(address, port);
}

const QList<WebSocket *> &WebSocketServer::Get_web_socket_group_() const
{
    return web_socket_group_;
}

void WebSocketServer::OnNewConnection()
{
    QWebSocket *qweb_socket = web_socket_server_->nextPendingConnection();
    WebSocket *web_socket = CreateWebSocket(qweb_socket);

    if(web_socket != nullptr) {
        web_socket_group_.append(web_socket);
        connect(qweb_socket, &QWebSocket::disconnected, this, [=]{
            web_socket_group_.removeOne(web_socket);
        });
        emit OnCreatedWebSocket(web_socket);
    }
    else {
        qweb_socket->close();
        qweb_socket->deleteLater();
    }
}

WebSocket *WebSocketServer::CreateWebSocket(QWebSocket *qweb_socket)
{
    QString path = qweb_socket->requestUrl().path();

    for(const auto &set : bind_data_group_) {
        QRegularExpression re(set.path);
        QRegularExpressionMatch match = re.match(path);
        if(match.hasMatch()) {
            return set.create(qweb_socket);
        }
    }

    return nullptr;
}

const QList<WebSocketServer::BindData> &WebSocketServer::Get_bind_data_group_() const
{
    return bind_data_group_;
}
