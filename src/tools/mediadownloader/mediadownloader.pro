TEMPLATE = app
TARGET = mediadownloader
QT += network

SOURCES += Main.cpp MediaDownloader.cpp

HEADERS += MediaDownloader.h

LIBS *= -lwikt
LIBS += -L../../../bin

INCLUDEPATH += ../..
DESTDIR = ../../../bin
