TEMPLATE = app
TARGET = convdict34

SOURCES += \
  format4writer.cpp \
  languagestatistic.cpp \
  licensepagesgenerator.cpp \
  linkconverter.cpp \
  main.cpp \
  statspagegenerator.cpp \
  titlepagegenerator.cpp

HEADERS += \
  format4writer.h \
  languagestatistic.h \
  licensepagesgenerator.h \
  linkconverter.h \
  statspagegenerator.h \
  titlepagegenerator.h

LIBS *= -lwikt
LIBS += -L../../../bin
INCLUDEPATH += ../..
DESTDIR = ../../../bin
