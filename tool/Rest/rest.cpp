#include "worker.h"

#include <QThread>

Worker::Worker(int max_thread_number, QObject *parent) : QObject (parent)
{
    for(int i=0;i<max_thread_number;++i) {
        QThread *thread = new QThread;
        thread->start();
        thread_data_group_.append({thread, {}});
    }
}

Worker::~Worker()
{
    while(!thread_data_group_.empty()) {
        auto &thread_data = thread_data_group_.first();
        thread_data.thread->quit();
        thread_data.thread->deleteLater();

        thread_data_group_.removeFirst();
    }
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
