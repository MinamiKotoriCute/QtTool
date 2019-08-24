#ifndef WORKER_H
#define WORKER_H

#include <functional>
#include <QObject>
#include <QVector>
#include <QList>

class QThread;

class Worker : public QObject
{
    Q_OBJECT
    struct ThreadData
    {
        QThread *thread;
        QList<QObject *> object_group;
    };

public:
    explicit Worker(int max_thread_number = 1, QObject *parent = nullptr);
    ~Worker();


signals:

public slots:
    void MoveToThread(QObject *object);

private:
    ThreadData& FindLeastObjectThreadData();

    QVector<ThreadData> thread_data_group_;
};

#endif // WORKER_H
