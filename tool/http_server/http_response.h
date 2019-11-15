#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QObject>
#include <QMap>

class HttpResponse : public QObject
{
    Q_OBJECT
public:
    explicit HttpResponse(QObject *parent = nullptr);

    void EasyText(QByteArray data);
    void EasyJson(QByteArray data);
    void EasyNotFound(QByteArray data);

    void SetAccessControlAll();

    QMap<QString,QString>& header_group(){return header_group_;}

    QByteArray Data() const;

signals:

public slots:

private:
    QByteArray status_code_;
    QByteArray body_;
    QMap<QString,QString> header_group_;
};

#endif // HTTPRESPONSE_H
