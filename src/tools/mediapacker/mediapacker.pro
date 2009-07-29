TEMPLATE = app
TARGET = mediapacker

SOURCES += Main.cpp MediaWriter.cpp
HEADERS += MediaWriter.h

LIBS *= -lwikt
LIBS += -L../../../bin

INCLUDEPATH += ../../lib
DESTDIR = ../../../bin
