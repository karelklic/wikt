TEMPLATE = app
TARGET = wiktsrc
SOURCES += main.cpp
LIBS *= -lwikt
LIBS += -L../../../bin
INCLUDEPATH += ../..
DESTDIR = ../../../bin
