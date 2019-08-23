QT += websockets

CurrentPath = $$PWD

INCLUDEPATH += $$CurrentPath

SOURCES += \
    $$CurrentPath/websocketserver.cpp \
    $$CurrentPath/websocket.cpp

HEADERS += \
    $$CurrentPath/websocketserver.h \
    $$CurrentPath/websocket.h
