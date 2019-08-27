#include "web_server.h"

#include "http_server.h"
#include "http_connection.h"
#include "http_request.h"
#include "web_handler.h"

WebServer::WebServer(HttpServer *http_server, QObject *parent) :
    QObject (parent),
    http_server_(http_server ? http_server : new HttpServer)
{
    connect(http_server_, &HttpServer::OnCreatedConnection, http_server_, [=](HttpConnection *http_connection){
        connect(http_connection, &HttpConnection::OnRequest, http_connection, [=](){
            const auto &key = http_connection->http_request().subpath();
            auto web_handler_normal_it = web_handler_normal_group_.find(key);
            if(web_handler_normal_it != web_handler_normal_group_.end()) {
                auto handler = (*web_handler_normal_it)(http_connection);
            }
        });
    });
}

bool WebServer::Listen(quint16 port, const QHostAddress &address)
{
    return http_server_->Listen(port, address);
}
