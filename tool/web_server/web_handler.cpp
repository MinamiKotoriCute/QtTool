#include "web_handler.h"

#include "http_connection.h"

WebHandler::WebHandler(HttpConnection *http_connection, QObject *parent) : QObject(parent)
{
    connect(http_connection)
}
