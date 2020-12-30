QT += core network gui widgets

TARGET = Server
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += debug_and_release

HEADERS += \
    cards.h \
    chatserver.h \
    serverworker.h \
    serverwindow.h

SOURCES += \
    cards.cpp \
    chatserver.cpp \
    servermain.cpp \
    serverworker.cpp \
    serverwindow.cpp

FORMS += \
    serverwindow.ui
