!command_line {
CONFIG += command_line

QT += core

CurrentPath = $$PWD

INCLUDEPATH += $$CurrentPath

SOURCES += \
    $$CurrentPath/command_line.cpp

HEADERS += \
    $$CurrentPath/command_line.h

include(../../tool/function_wrapper_map/function_wrapper_map.pri)

}

HEADERS += \
    $$PWD/auto_complete_read_line.h \
    $$PWD/command.h

SOURCES += \
    $$PWD/auto_complete_read_line.cpp \
    $$PWD/command.cpp
