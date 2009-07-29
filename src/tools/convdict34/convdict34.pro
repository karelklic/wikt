TEMPLATE = app
TARGET = convdict34

SOURCES += \
  Format4Writer.cpp \
  LanguageStatistic.cpp \
  LicensePagesGenerator.cpp \
  LinkConverter.cpp \
  Main.cpp \
  StatsPageGenerator.cpp \
  TitlePageGenerator.cpp

HEADERS += \
  Format4Writer.h \
  LanguageStatistic.h \
  LicensePagesGenerator.h \
  LinkConverter.h \
  StatsPageGenerator.h \
  TitlePageGenerator.h

LIBS *= -lwikt
LIBS += -L../../../bin

INCLUDEPATH += ../../lib
DESTDIR = ../../../bin
