#include "http_server.h"

#include <QTcpServer>
#include <QTcpSocket>

#include "http_connection.h"
#include "http_response.h"
#include "http_request.h"

HttpServer::HttpServer(QTcpServer *qtcp_server, QObject *parent) :
    QObject(parent),
    qtcp_server_(qtcp_server ? qtcp_server : new QTcpServer)
{
    connect(qtcp_server_, &QTcpServer::newConnection, this, &HttpServer::OnNewConnection);
}

bool HttpServer::Listen(quint16 port, const QHostAddress &address)
{
    return qtcp_server_->listen(address, port);
}

void HttpServer::OnNewConnection()
{
    QTcpSocket *qtcp_socket = qtcp_server_->nextPendingConnection();

    HttpConnection *http_connection = new HttpConnection(qtcp_socket);
    http_connection_group_.append(http_connection);
    connect(qtcp_socket, &QTcpSocket::disconnected, this, [=]{
        http_connection_group_.removeOne(http_connection);
    });

    emit OnCreatedConnection(http_connection);
}
