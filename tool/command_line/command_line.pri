!command_line {
CONFIG += command_line

QT += core

CurrentPath = $$PWD

INCLUDEPATH += $$CurrentPath

SOURCES += \
    $$CurrentPath/command_line.cpp

HEADERS += \
    $$CurrentPath/command_line.h

include(../../tool/command_line/command_line.pri)

}
