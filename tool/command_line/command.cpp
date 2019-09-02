#include "command.h"

Command::Command(QString name)
{

}

Command::~Command()
{

}

void Command::ParserAndExcuttion(QString text)
{
    auto text_list = text.split(' ');


    Run();
}

QString Command::get_name()
{
    return name_;
}
