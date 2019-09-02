#ifndef COMMAND_H
#define COMMAND_H

#include <type_traits>
#include <QString>

#include "function_wrapper_map.h"

class Command
{
public:
    Command(QString name);
    virtual ~Command();

    void ParserAndExcuttion(QString text);

    QString get_name();

protected:
    template<typename T>
    auto Regist(QString parameter_name, T &t, bool is_required = false) {
        if(is_required)
            required_parameter_group_.append(parameter_name);
        function_wrapper_map_.regist(parameter_name, [&t](T &&new_t){
            t = std::move(new_t);
        });
        return const_cast<decltype(*this)>(*this);
    }

    virtual void Run() {}

private:
    QStringList required_parameter_group_;
    FunctionWrapperMap function_wrapper_map_;
    QString name_;
};

#endif // COMMAND_H
