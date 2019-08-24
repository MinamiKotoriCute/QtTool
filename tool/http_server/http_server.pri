QT += network

CurrentPath = $$PWD

INCLUDEPATH += $$CurrentPath

SOURCES += \
    $$CurrentPath/http_server.cpp \
    $$PWD/http_connection.cpp \
    $$PWD/http_request.cpp \
    $$PWD/http_response.cpp

HEADERS += \
    $$CurrentPath/http_server.h \
    $$PWD/http_connection.h \
    $$PWD/http_request.h \
    $$PWD/http_response.h
