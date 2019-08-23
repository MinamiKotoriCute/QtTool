QT += network

CurrentPath = $$PWD

INCLUDEPATH += $$CurrentPath

SOURCES += \
    $$CurrentPath/httpserver.cpp \
    $$PWD/httpconnection.cpp \
    $$PWD/httprequest.cpp \
    $$PWD/httpresponse.cpp

HEADERS += \
    $$CurrentPath/httpserver.h \
    $$PWD/httpconnection.h \
    $$PWD/httprequest.h \
    $$PWD/httpresponse.h
