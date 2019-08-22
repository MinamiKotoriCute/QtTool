#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QObject>
#include <QDebug>

class QWebSocket;

class WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WebSocket(QWebSocket *qweb_socket, QObject *parent = nullptr);
    virtual ~WebSocket();

signals:
    void SendMessage(const QString &text);

public slots:
    virtual void OnRelease() {}

protected slots:
    virtual void OnReceiveMessage(const QString &text) {Q_UNUSED(text)}

private:
    QWebSocket *qweb_socket_;
};

#endif // WEBSOCKET_H
