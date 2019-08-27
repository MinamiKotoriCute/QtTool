#pragma once

#include <functional>
#include <QObject>
#include <QHostAddress>
#include <QList>

class QTcpServer;
class HttpConnection;

class HttpServer : public QObject
{
    Q_OBJECT

public:
    explicit HttpServer(QTcpServer *qtcp_server = nullptr, QObject *parent = nullptr);

    bool Listen(quint16 port = 0, const QHostAddress &address = QHostAddress::Any);

signals:
    void OnCreatedConnection(HttpConnection *http_connection);

public slots:

private slots:
    void OnNewConnection();

private:
    QTcpServer *qtcp_server_;
    QList<HttpConnection*> http_connection_group_;
};
