include(../../../wikt.pri)

TEMPLATE = app
TARGET = dict3src
SOURCES += main.cpp
LIBS *= -lwikt
LIBS += -L../../../bin
INCLUDEPATH += ../..
DESTDIR = ../../../bin
