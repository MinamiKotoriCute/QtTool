#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "function_wrapper_map.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FunctionWrapperMap f;
    f.regist("asd", []{
        qDebug("Asd");
    });
    f.regist("QQ", [](int aa){
        qDebug("QQ %d", aa);
    });

    f.call({"asd"});
    f.call({QString("QQ"), "156"});

    return a.exec();
}
