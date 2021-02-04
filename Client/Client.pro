QT += core network gui widgets

TARGET = Client
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += debug_and_release

SOURCES += \
    clientmain.cpp \
    chatwindow.cpp \
    chatclient.cpp \
    cards.cpp

FORMS += \
    chatwindow.ui

HEADERS += \
    cards.h \
    chatwindow.h \
    chatclient.h