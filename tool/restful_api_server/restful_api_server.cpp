#include "restful_api_server.h"

#include "http_server.h"
#include "http_connection.h"

RestfulApiServer::RestfulApiServer(HttpServer *http_server, QObject *parent) :
    QObject (parent),
    http_server_(http_server ? http_server : new HttpServer(nullptr ,this))
{
    connect(http_server_, &HttpServer::OnCreatedConnection, this, [](HttpConnection *http_connection){
        connect(http_connection, &HttpConnection::OnRequest,
    });
}
