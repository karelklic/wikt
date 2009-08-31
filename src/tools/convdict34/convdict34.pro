include(../tools.pri)

TEMPLATE = app
TARGET = convdict34

SOURCES += \
  categorybuilder.cpp \
  format4writer.cpp \
  languagestatistic.cpp \
  licensepagesgenerator.cpp \
  linkconverter.cpp \
  main.cpp \
  statspagegenerator.cpp \
  titlepagegenerator.cpp

HEADERS += \
  categorybuilder.h \
  format4writer.h \
  languagestatistic.h \
  licensepagesgenerator.h \
  linkconverter.h \
  statspagegenerator.h \
  titlepagegenerator.h

INCLUDEPATH += ../..
DESTDIR = ../../../bin
