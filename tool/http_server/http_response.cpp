#include "http_response.h"

HttpResponse::HttpResponse(QObject *parent) : QObject(parent)
{

}

void HttpResponse::EasyText(QByteArray data)
{
    body_ = data;
    status_code_ = "200 OK";
    header_group_["Content-Type"] = "text/html";
    header_group_["Content-Length"] = QString::number(data.size());
}

void HttpResponse::EasyJson(QByteArray data)
{
    body_ = data;
    status_code_ = "200 OK";
    header_group_["Content-Type"] = "application/json";
    header_group_["Content-Length"] = QString::number(data.size());
}

void HttpResponse::EasyNotFound(QByteArray data)
{
    body_ = data;
    status_code_ = "404 Not Found";
    header_group_["Content-Type"] = "text/html";
    header_group_["Content-Length"] = QString::number(data.size());
}

QByteArray HttpResponse::Data() const
{
    QByteArray data;
    data += "HTTP/1.1 " + status_code_ + "\r\n";
    for(auto it = header_group_.constBegin(); it != header_group_.constEnd(); ++it) {
        data += it.key() + ": " + it.value() + "\r\n";
    }
    data += "\r\n" + body_;
    return data;
}
