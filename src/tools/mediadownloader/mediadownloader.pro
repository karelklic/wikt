TEMPLATE = app
TARGET = mediadownloader
QT += network

SOURCES += main.cpp mediadownloader.cpp

HEADERS += mediadownloader.h

LIBS *= -lwikt
LIBS += -L../../../bin

INCLUDEPATH += ../..
DESTDIR = ../../../bin
