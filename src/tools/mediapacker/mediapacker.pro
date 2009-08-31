include(../tools.pri)

TEMPLATE = app
TARGET = mediapacker
SOURCES += main.cpp mediawriter.cpp
HEADERS += mediawriter.h
INCLUDEPATH += ../..
DESTDIR = ../../../bin
