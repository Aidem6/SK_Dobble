QT += core network gui widgets

TARGET = Dobble
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += debug_and_release

SOURCES += \
    main.cpp \
    window.cpp \
    client.cpp

FORMS += \
    window.ui

HEADERS += \
    cards.h \
    window.h \
    client.h
