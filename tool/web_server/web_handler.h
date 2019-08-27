#ifndef WEB_HANDLER_H
#define WEB_HANDLER_H

#include <QObject>

class HttpConnection;

class WebHandler : public QObject
{
    Q_OBJECT
public:
    explicit WebHandler(HttpConnection *http_connection, QObject *parent = nullptr);

signals:

public slots:

private:
    HttpConnection *http_connection_;
};

#endif // WEB_HANDLER_H
