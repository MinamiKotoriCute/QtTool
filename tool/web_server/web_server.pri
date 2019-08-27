!web_server {
CONFIG += web_server
QT += network

CurrentPath = $$PWD

INCLUDEPATH += $$CurrentPath

SOURCES += \
    $$CurrentPath/web_server.cpp

HEADERS += \
    $$CurrentPath/web_server.h

include(../../tool/http_server/http_server.pri)
}

HEADERS += \
    $$PWD/web_handler.h

SOURCES += \
    $$PWD/web_handler.cpp
