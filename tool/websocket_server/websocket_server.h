#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <functional>
#include <QObject>
#include <QHostAddress>

class QWebSocket;
class QWebSocketServer;
class WebSocket;

class WebSocketServer : public QObject
{
    Q_OBJECT
    struct BindData
    {
        QString path;
        std::function<WebSocket*(QWebSocket*)> create;
    };

public:
    explicit WebSocketServer(QObject *parent = nullptr);
    virtual ~WebSocketServer();

    template<typename T>
    WebSocketServer& Bind(QString url)
    {
        bind_data_group_.append({url, [](QWebSocket *web_socket){return new T(web_socket);}});
        return *this;
    }
    bool Listen(quint16 port = 0, const QHostAddress &address = QHostAddress::Any);
    const QList<WebSocket*>& Get_web_socket_group_() const;

signals:
    void OnCreatedWebSocket(WebSocket *web_socket);

public slots:

private slots:
    void OnNewConnection();

protected:
    virtual WebSocket* CreateWebSocket(QWebSocket *qweb_socket);
    const QList<BindData>& Get_bind_data_group_() const;

private:
    QList<WebSocket*> web_socket_group_;
    QList<BindData> bind_data_group_;
    QWebSocketServer *web_socket_server_;
};

#endif // WEBSOCKETSERVER_H
