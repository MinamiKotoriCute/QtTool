#ifndef WORKER_H
#define WORKER_H

#include <functional>
#include <QObject>
#include <QVector>
#include <QList>
#include <QMap>
#include <QHostAddress>

//#include "web_handler.h"

class HttpServer;
class WebHandler;
class HttpConnection;

class WebServer : public QObject
{
    Q_OBJECT
public:
    explicit WebServer(HttpServer *http_server = nullptr, QObject *parent = nullptr);
    ~WebServer();

    template<typename WebHandler>
    void RegistRestfulApi(QString key)
    {
        web_handler_normal_group_.insert(key, [](HttpConnection *http_connection){
            return new WebHandler(http_connection);
        });
    }

    bool Listen(quint16 port = 0, const QHostAddress &address = QHostAddress::Any);

signals:

public slots:

private slots:

private:
    QMap<QString, std::function<WebHandler*(HttpConnection*)>> web_handler_normal_group_;
    HttpServer *http_server_;
};

#endif // WORKER_H
