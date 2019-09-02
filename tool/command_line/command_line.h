#ifndef WORKER_H
#define WORKER_H

#include <functional>
#include <memory>

#include <QThread>
#include <QVector>
#include <QList>

#include "command.h"
#include "auto_complete_read_line.h"

class CommandLine : public QThread
{
    Q_OBJECT

public:
    explicit CommandLine(QObject *parent = nullptr);

    std::unique_ptr<AutoCompleteReadLine> set_read_line(std::unique_ptr<AutoCompleteReadLine> read_line);

    template<typename T>
    void Regist(QString command_name) {
        command_group_.insert(command_name, []{return std::make_unique<T>();});
    }

signals:

public slots:

protected:
    void run() override;

private:
    void UpdateAutoCompleteHandler();
    void ProcessOneCommand();

    QMap<QString, std::function<std::unique_ptr<Command>()>> command_group_;
    std::unique_ptr<AutoCompleteReadLine> read_line_;
};

#endif // WORKER_H
