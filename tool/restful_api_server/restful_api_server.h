#ifndef WORKER_H
#define WORKER_H

#include <functional>
#include <QObject>
#include <QVector>
#include <QList>

class HttpServer;

class RestfulApiServer : public QObject
{
    Q_OBJECT

public:
    explicit RestfulApiServer(HttpServer *http_server = nullptr, QObject *parent = nullptr);
    ~RestfulApiServer();


signals:

public slots:

private:
    HttpServer *http_server_;
};

#endif // WORKER_H
