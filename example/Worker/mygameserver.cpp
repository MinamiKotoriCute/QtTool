#include "mygameserver.h"

#include "websocket.h"

MyGameServer::MyGameServer(QObject *parent) : WebSocketServer(parent)
{

}

void MyGameServer::KickAll()
{
    for(auto &web_socket : Get_web_socket_group_()) {
        emit web_socket->OnRelease();
    }
}
