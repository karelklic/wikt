TEMPLATE = app
TARGET = mediadownloader
SOURCES += main.cpp

LIBS *= -lwikt
LIBS += -L../../../bin
INCLUDEPATH += ../..
DESTDIR = ../../../bin
