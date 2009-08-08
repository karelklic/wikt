include(../../../wikt.pri)

TEMPLATE = app
TARGET = wikitoxml
SOURCES += main.cpp
LIBS *= -lwikt
LIBS += -L../../../bin
INCLUDEPATH += ../..
DESTDIR = ../../../bin
