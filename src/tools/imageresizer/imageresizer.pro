TEMPLATE = app
TARGET = imageresizer

SOURCES += Main.cpp

LIBS *= -lwikt
LIBS += -L../../../bin

INCLUDEPATH += ../../lib
DESTDIR = ../../../bin
