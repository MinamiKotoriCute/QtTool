#pragma once

#include <functional>
#include <vector>
#include <map>

#include <QString>
#include <QTextStream>
#include <QDataStream>

template<typename Parameter,
         template<typename> typename ParameterTransform,
         typename Key = Parameter,
         typename ParameterContainer = std::vector<Parameter>,
         typename KeyContainer = std::vector<Key>>
class basic_FunctionWrapperMap
{
public:
    using parameter_container = ParameterContainer;
    using parameter_iterator = typename parameter_container::iterator;
    using parameter_const_iterator = typename parameter_container::const_iterator;

private:
    struct FunctionData
    {
        std::function<void(parameter_iterator, parameter_iterator)> handleFunction;
        std::function<void(parameter_const_iterator, parameter_const_iterator)> constHandleFunction;
        parameter_container parameter;
    };

    template<typename... Args, std::size_t... I>
    static FunctionData createHandleFunction(void(*handleFunction)(Args...), std::index_sequence<I...>)
    {
        return { [handleFunction](parameter_iterator begin, parameter_iterator end) {
            if (end - begin != sizeof...(Args))
                throw std::exception("parameter number not match.");
            handleFunction(ParameterTransform<std::remove_const_t<std::remove_reference_t<Args>>>()(std::move(*(begin + I)))...);
        },[handleFunction](parameter_const_iterator begin, parameter_const_iterator end) {
                if (end - begin != sizeof...(Args))
                    throw std::exception("parameter number not match.");
                handleFunction(ParameterTransform<std::remove_const_t<std::remove_reference_t<Args>>>()(*(begin + I))...);
        },{ typeid(Args).name()... }
        };
    }
    template<typename... Args, typename CallableObject, std::size_t... I>
    static FunctionData createHandleFunction(const CallableObject &handleFunction, std::index_sequence<I...>)
    {
        return { [handleFunction](parameter_iterator begin, parameter_iterator end) {
            if (end - begin != sizeof...(Args))
                throw std::exception("parameter number not match.");
            handleFunction(ParameterTransform<std::remove_const_t<std::remove_reference_t<Args>>>()(std::move(*(begin + I)))...);
        },[handleFunction](parameter_const_iterator begin, parameter_const_iterator end) {
                    if (end - begin != sizeof...(Args))
                        throw std::exception("parameter number not match.");
                    handleFunction(ParameterTransform<std::remove_const_t<std::remove_reference_t<Args>>>()(*(begin + I))...);
        },{ typeid(Args).name()... }
        };
    }
    template<typename... Args, typename CallableObject, std::size_t... I>
    static FunctionData createHandleFunction(CallableObject &&handleFunction, std::index_sequence<I...>)
    {
        return { [handleFunction = std::forward<CallableObject>(handleFunction)](parameter_iterator begin, parameter_iterator end) {
            if (end - begin != sizeof...(Args))
                throw std::exception("parameter number not match.");
            handleFunction(ParameterTransform<std::remove_const_t<std::remove_reference_t<Args>>>()(std::move(*(begin + I)))...);
        },[handleFunction = std::forward<CallableObject>(handleFunction)](parameter_const_iterator begin, parameter_const_iterator end) {
                if (end - begin != sizeof...(Args))
                    throw std::exception("parameter number not match.");
                handleFunction(ParameterTransform<std::remove_const_t<std::remove_reference_t<Args>>>()(*(begin + I))...);
        },{ typeid(Args).name()... }
        };
    }

    template<typename Other, typename CallableObject>
    struct regist_helper {};
    template<typename RT, typename Class, typename... Args, typename CallableObject>
    struct regist_helper<RT(Class::*)(Args...), CallableObject>
    {
        static auto regist(const CallableObject &handleFunction)
        {
            return basic_FunctionWrapperMap::createHandleFunction<Args...>(handleFunction, std::make_index_sequence<sizeof...(Args)>());
        }
        static auto regist(CallableObject &&handleFunction)
        {
            return basic_FunctionWrapperMap::createHandleFunction<Args...>(std::forward<CallableObject>(handleFunction), std::make_index_sequence<sizeof...(Args)>());
        }
    };
    template<typename RT, typename Class, typename... Args, typename CallableObject>
    struct regist_helper<RT(Class::*)(Args...) const, CallableObject>
    {
        static auto regist(const CallableObject &handleFunction)
        {
            return basic_FunctionWrapperMap::createHandleFunction<Args...>(handleFunction, std::make_index_sequence<sizeof...(Args)>());
        }
        static auto regist(CallableObject &&handleFunction)
        {
            return basic_FunctionWrapperMap::createHandleFunction<Args...>(std::forward<CallableObject>(handleFunction), std::make_index_sequence<sizeof...(Args)>());
        }
    };

public:
    template<typename... Args>
    void regist(const Key &key, void(*handleFunction)(Args...))
    {
        container[key] = createHandleFunction(handleFunction, std::make_index_sequence<sizeof...(Args)>());
    }

    template<typename CallableObject>
    void regist(const Key &key, const CallableObject &handleFunction)
    {
        container[key] = regist_helper<decltype(&CallableObject::operator()), CallableObject>::regist(handleFunction);
    }
    template<typename CallableObject>
    void regist(const Key &key, CallableObject &&handleFunction)
    {
        container[key] = regist_helper<decltype(&std::remove_reference_t<CallableObject>::operator()), std::remove_reference_t<CallableObject>>::regist(std::forward<CallableObject>(handleFunction));
    }

    bool call(const parameter_container &command)
    {
        auto it = container.find(command.front());
        if (it == container.end())
            return false;

        it->second.constHandleFunction(command.begin() + 1, command.end());
        return true;
    }

    bool call(parameter_container &&command)
    {
        auto it = container.find(command.front());
        if (it == container.end())
            return false;

        it->second.handleFunction(command.begin() + 1, command.end());
        return true;
    }

    KeyContainer GetKeyGroup() const {
        KeyContainer c;
        for(const auto &p : container) {
            c.push_back(p.first);
        }
        return c;
    }

protected:
    std::map<Key, FunctionData> container;
};

template<typename T>
struct ParameterTransform
{
    T operator()(const QString &s)
    {
        QString s2 = s;
        T t;
        QTextStream ss(&s2);
        ss >> t;
        return t;
    }
    T operator()(QString &&s)
    {
        T t;
        QTextStream ss(&s);
        ss >> t;
        return t;
    }
};

using FunctionWrapperMap = basic_FunctionWrapperMap<QString, ParameterTransform, QString, QVector<QString>, QVector<QString>>;

