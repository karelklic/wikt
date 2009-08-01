TEMPLATE = app
TARGET = convdict12

SOURCES += format2.cpp main.cpp
HEADERS += format2.h

LIBS *= -lwikt
LIBS += -L../../../bin
INCLUDEPATH += ../..
DESTDIR = ../../../bin
