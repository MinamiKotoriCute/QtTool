#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <QObject>

#include "httprequest.h"

class QTcpSocket;

class HttpConnection : public QObject
{
    Q_OBJECT
public:
    explicit HttpConnection(QTcpSocket *qtcp_socket, QObject *parent = nullptr);

signals:
    void OnRequest(const HttpRequest &http_request);

public slots:
    void Write(QByteArray data);

private slots:
    void OnReadyRead();
    void OnByteWritten(qint64 bytes);

private:
    HttpRequest http_request_;
    qint64 totalWriteSize = -1;
    qint64 alreadyWriteBytes = 0;
    QTcpSocket *qtcp_socket_;
};

#endif // HTTPCONNECTION_H
