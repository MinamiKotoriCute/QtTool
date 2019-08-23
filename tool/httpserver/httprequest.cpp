#include "httprequest.h"

#include <QRegularExpression>
#include <QDebug>

HttpRequest::HttpRequest(QObject *parent) : QObject(parent)
{

}

bool HttpRequest::Parser(QByteArray request_packet)
{
    //qDebug() << request_packet;

    int request_header_length = request_packet.indexOf("\r\n\r\n");
    if(request_header_length < 0)
        return false;
    else
        request_body_ = request_packet.mid(request_header_length + 5);
    //QString request_front = QUrl::fromPercentEncoding(request_packet.left(request_header_length));
    QByteArray request_front = request_packet.left(request_header_length);

    QList<QByteArray> request_header = request_front.split('\r');
    QByteArray request_line;
    if(request_header.size() >= 1) {
        request_line = request_header.first();
        request_header.removeFirst();
    }
    for(auto &header : request_header) {
        if(header.size() > 0 && header[0] == '\n') {
            header.remove(0,1);
        }
    }
    //qDebug() << '\n' << request_line;

    QRegularExpression re(R"##((\w+) (.+) (\w+)/(\S+))##");
    QRegularExpressionMatch match = re.match(request_line);
    QString protocal;
    if(match.hasMatch() && match.capturedTexts().size() >= 5) {
        method_ = match.captured(1);
        subpath_ = match.captured(2);
        protocal = match.captured(3);
        http_version_ = match.captured(4);
    }
    else
        return false;

    for(auto header : request_header) {
        int key_length = header.indexOf(':');
        if(key_length > 0) {
            QByteArray key = header.left(key_length);
            if(header.size() <= key_length + 2)
                return false;
            QByteArray value = header.mid(key_length + 2); // ": "
            header_group_.insert(key, value);
            //qDebug() << key << value;
        }
        else
            return false;
    }

    return true;
}
