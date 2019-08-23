QT += websockets

CurrentPath = $$PWD

INCLUDEPATH += $$CurrentPath

SOURCES += \
    $$CurrentPath/worker.cpp

HEADERS += \
    $$CurrentPath/worker.h
