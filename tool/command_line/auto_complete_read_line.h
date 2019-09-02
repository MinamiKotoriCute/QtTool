#ifndef AUTO_COMPLETE_READ_LINE_H
#define AUTO_COMPLETE_READ_LINE_H

#include <QObject>

#include <functional>

class AutoCompleteReadLine : public QObject
{
    Q_OBJECT
public:
    explicit AutoCompleteReadLine(QObject *parent = nullptr);

    QString ReadLine();

    std::function<QStringList(QString text, int index)> OnAutoCompleteHandler;
};

#endif // AUTO_COMPLETE_READ_LINE_H
