#include "http_connection.h"

#include <QTcpSocket>
#include <QUrl>
#include <QRegularExpression>
#include <QTimer>
#include <QDebug>

HttpConnection::HttpConnection(QTcpSocket *qtcp_socket, QObject *parent) :
    QObject(parent),
    qtcp_socket_(qtcp_socket)
{    
    connect(qtcp_socket_, &QTcpSocket::readyRead, this, &HttpConnection::OnReadyRead);
    connect(qtcp_socket_, &QTcpSocket::bytesWritten, this, &HttpConnection::OnByteWritten);
    connect(qtcp_socket_, &QTcpSocket::disconnected, this, &HttpConnection::deleteLater);
    connect(qtcp_socket_, &QTcpSocket::disconnected, qtcp_socket_, &QTcpSocket::deleteLater);
}

void HttpConnection::Write(QByteArray data)
{
    if(totalWriteSize >= 0)
        return;

    totalWriteSize = data.size();
    QTimer::singleShot(0, qtcp_socket_, [=]{
        qtcp_socket_->write(data);
    });
}

void HttpConnection::OnReadyRead()
{
    QByteArray request_packet = qtcp_socket_->readAll();

    if(http_request_.Parser(request_packet))
        emit OnRequest(http_request_);
    else {
        QTimer::singleShot(0, qtcp_socket_, [=]{
            qtcp_socket_->disconnectFromHost();
        });
    }
}

void HttpConnection::OnByteWritten(qint64 bytes)
{
    alreadyWriteBytes += bytes;

    if(alreadyWriteBytes == totalWriteSize) {
        QTimer::singleShot(0, qtcp_socket_, [=]{
            qtcp_socket_->disconnectFromHost();
        });
    }
}
