!restful_api_server {
CONFIG += restful_api_server
QT += network

CurrentPath = $$PWD

INCLUDEPATH += $$CurrentPath

SOURCES += \
    $$CurrentPath/restful_api_server.cpp

HEADERS += \
    $$CurrentPath/restful_api_server.h

include(../../tool/http_server/http_server.pri)
}
