#include "command_line.h"

#include <iostream>
#include <QTextStream>
#include <QDebug>

CommandLine::CommandLine(QObject *parent) :
    QThread (parent),
    read_line_(std::make_unique<AutoCompleteReadLine>()),
    prefix_("> ")
{

}

std::unique_ptr<AutoCompleteReadLine> CommandLine::set_read_line(std::unique_ptr<AutoCompleteReadLine> read_line)
{
    auto old_read_line = std::move(read_line_);
    read_line_ = std::move(read_line);
    return old_read_line;
}

QString CommandLine::prefix() const
{
    return prefix_;
}

void CommandLine::set_prefix(QString prefix)
{
    prefix_ = prefix;
}

void CommandLine::run()
{
    for(;;) {
        try {
            std::cout << qPrintable(prefix_);
            ProcessOneCommand();
        } catch (std::exception &ex) {
            qWarning() << ex.what();
        } catch (...) {
            qWarning() << "Capture unknow exception";
        }
    }
}

void CommandLine::UpdateAutoCompleteHandler()
{
    read_line_->OnAutoCompleteHandler = [](QString text, int index) -> QStringList {
        qDebug("want auto");
        return {};
    };
}

void CommandLine::ProcessOneCommand()
{
    auto read_text = read_line_->ReadLine();

    QString command_name;
    QString command_parameter;
    auto index = read_text.indexOf(' ');
    if(index == -1)
        command_name = read_text;
    else {
        command_name = read_text.left(index);
        command_parameter = read_text.mid(index+1);
    }

    auto command_it = command_group_.find(command_name);
    if(command_it == command_group_.end())
        throw std::exception("command not find");

    auto command = (*command_it)();
    command->ParserAndExcuttion(command_parameter);
}

