#ifndef MYGAMESERVER_H
#define MYGAMESERVER_H

#include <QObject>

#include "websocketserver.h"

class MyGameServer : public WebSocketServer
{
    Q_OBJECT
public:
    explicit MyGameServer(QObject *parent = nullptr);

signals:

public slots:
    void KickAll();
};

#endif // MYGAMESERVER_H
