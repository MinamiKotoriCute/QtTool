QT += websockets

CurrentPath = $$PWD

INCLUDEPATH += $$CurrentPath

SOURCES += \
    $$CurrentPath/websocket_server.cpp \
    $$CurrentPath/websocket.cpp

HEADERS += \
    $$CurrentPath/websocket_server.h \
    $$CurrentPath/websocket.h
