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

    using HandleFunctionType = std::function<QByteArray(const QString &url, const QMap<QString,QString> &request)>;
public:
    explicit HttpServer(QTcpServer *qtcp_server = nullptr, QObject *parent = nullptr);

    bool Listen(quint16 port = 0, const QHostAddress &address = QHostAddress::Any);
    void setHandler(HandleFunctionType &&f);

signals:
    void OnCreatedConnection(HttpConnection *http_connection);

public slots:

private slots:
    void OnNewConnection();

private:
    HandleFunctionType m_handler;
    QTcpServer *qtcp_server_;
    QList<HttpConnection*> http_connection_group_;
};
