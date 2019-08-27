#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QMap>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequest(QObject *parent = nullptr);

    bool Parser(QByteArray request_packet);

    QString method() const {return method_;}
    QString subpath() const {return subpath_;}
    QString http_version() const {return http_version_;}
    QByteArray request_body() const {return request_body_;}
    const QMap<QString,QString>& header_group() const {return header_group_;}

private:
    QString method_;
    QString subpath_;
    QString http_version_;
    QByteArray request_body_;
    QMap<QString,QString> header_group_;
};

#endif // HTTPREQUEST_H
