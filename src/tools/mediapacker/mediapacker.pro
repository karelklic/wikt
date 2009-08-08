include(../../../wikt.pri)

TEMPLATE = app
TARGET = mediapacker

SOURCES += main.cpp mediawriter.cpp
HEADERS += mediawriter.h

LIBS *= -lwikt
LIBS += -L../../../bin

INCLUDEPATH += ../..
DESTDIR = ../../../bin
