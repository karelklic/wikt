include(../../../wikt.pri)

TEMPLATE = app
TARGET = dict4src
SOURCES += main.cpp
LIBS *= -lwikt
LIBS += -L../../../bin
INCLUDEPATH += ../..
DESTDIR = ../../../bin
