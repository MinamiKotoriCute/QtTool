#ifndef MYUSER_H
#define MYUSER_H

#include <QObject>

#include "websocket.h"

class MyUser : public WebSocket
{
    Q_OBJECT
public:
    explicit MyUser(QWebSocket *qweb_socket, QObject *parent = nullptr);

signals:

public slots:

protected slots:
    void OnRelease() override;
    void OnReceiveMessage(const QString &text) override;
};

#endif // MYUSER_H
