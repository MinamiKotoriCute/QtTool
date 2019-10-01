#include "worker.h"

#include <QThread>
#include <QEventLoop>
#include <QDebug>

Worker::Worker(QObject *parent) : QObject (parent)
{
}

Worker::~Worker()
{
    Stop();
}

int Worker::ThreadNumber() const
{
    return thread_data_group_.size();
}

void Worker::Start(int thread_number)
{
    StopWait();

    for(int i=0;i<thread_number;++i) {
        QThread *thread = new QThread;
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        thread->start();
        thread_data_group_.append({thread, {}});
    }
}

void Worker::StartWait(int thread_number)
{
    StopWait();

    QEventLoop qevent_loop;
    int remaining_starting_thread_number = thread_number;
    for(int i=0;i<thread_number;++i) {
        QThread *thread = new QThread;
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(thread, &QThread::started, this, [&remaining_starting_thread_number, &qevent_loop]{
            if(--remaining_starting_thread_number == 0)
                qevent_loop.quit();
        });
        thread->start();
        thread_data_group_.append({thread, {}});
    }
    qevent_loop.exec();
}

void Worker::Stop()
{
    while(!thread_data_group_.empty()) {
        auto &thread_data = thread_data_group_.last();
        for(auto &object : thread_data.object_group) {
            connect(object, &QObject::destroyed, this, [object, &thread_data]{
                thread_data.object_group.removeOne(object);
            });
            object->deleteLater();
        }
        thread_data.thread->quit();

        thread_data_group_.removeLast();
    }
}

void Worker::StopWait()
{
    if(thread_data_group_.isEmpty())
        return;

    QEventLoop qevent_loop;
    int remaining_stoping_thread_number = thread_data_group_.size();
    while(!thread_data_group_.empty()) {
        auto &thread_data = thread_data_group_.last();
        for(auto &object : thread_data.object_group) {
            connect(object, &QObject::destroyed, this, [object, &thread_data]{
                thread_data.object_group.removeOne(object);
            });
            object->deleteLater();
        }
        connect(thread_data.thread, &QThread::finished, this, [&remaining_stoping_thread_number, &qevent_loop]{
            if(--remaining_stoping_thread_number == 0)
                qevent_loop.quit();
        });
        thread_data.thread->quit();
        thread_data_group_.removeLast();
    }
    qevent_loop.exec();
}

void Worker::MoveToThread(QObject *object)
{
    auto &thread_data = FindLeastObjectThreadData();
    thread_data.object_group.append(object);
    object->moveToThread(thread_data.thread);
    connect(object, &QObject::destroyed, this, [object, &thread_data]{
        thread_data.object_group.removeOne(object);
    });
}

void Worker::MoveToSpecificThread(int thread_index, QObject *object)
{
    if(thread_index < 0 || thread_index >=ThreadNumber())
        throw std::out_of_range("Worker thread index out of range");

    auto &thread_data = thread_data_group_[thread_index];
    thread_data.object_group.append(object);
    object->moveToThread(thread_data.thread);
    connect(object, &QObject::destroyed, this, [object, &thread_data]{
        thread_data.object_group.removeOne(object);
    });
}

Worker::ThreadData &Worker::FindLeastObjectThreadData()
{
    ThreadData *thread_data = &thread_data_group_.first();
    for(int i=1;i<thread_data_group_.size();++i) {
        if(thread_data->object_group.size() > thread_data_group_[i].object_group.size()) {
            thread_data = &thread_data_group_[i];
        }
    }
    return *thread_data;
}
