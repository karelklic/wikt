TEMPLATE = app
TARGET = imageresizer

SOURCES += main.cpp

LIBS *= -lwikt
LIBS += -L../../../bin

INCLUDEPATH += ../..
DESTDIR = ../../../bin
