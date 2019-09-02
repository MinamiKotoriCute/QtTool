#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "command_line.h"

class Hello : public Command
{
public:
    Hello() : Command("Hello") {
        Regist("i", i);
    }

    void Run() override {
        qDebug("Heeeeeeeeeeelo");
    }

private:
    int i;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    CommandLine c;
    c.Regist<Hello>("hello");

    c.start();

    return a.exec();
}
