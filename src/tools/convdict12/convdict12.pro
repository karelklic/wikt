TEMPLATE = app
TARGET = convdict12

SOURCES += Format2.cpp Main.cpp
HEADERS += Format2.h

LIBS *= -lwikt
LIBS += -L../../../bin

INCLUDEPATH += ../..
DESTDIR = ../../../bin
