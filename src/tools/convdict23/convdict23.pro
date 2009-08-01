TEMPLATE = app
TARGET = convdict23
DESTDIR = ../../../bin

SOURCES += \
  exprparser/exprdriver.cpp \
  exprparser/exprparser.tab.cpp \
  exprparser/exprscanner.cpp \
  format2reader.cpp \
  format3writer.cpp \
  formattingfunctions.cpp \
  galleryconverter.cpp \
  main.cpp \
  namespaceurlfunctions.cpp \
  pagenamefunctions.cpp \
  parameterlist.cpp \
  parserfunctions.cpp \
  templatesolver.cpp \
  templateutils.cpp

HEADERS += \
  exprparser/exprdriver.h \
  exprparser/exprparser.tab.hpp \
  exprparser/location.hh \
  exprparser/position.hh \
  exprparser/stack.hh \
  format2reader.h \
  format3writer.h \
  formattingfunctions.h \
  galleryconverter.h \
  namespaceurlfunctions.h \
  pagenamefunctions.h \
  parameterlist.h \
  parserfunctions.h \
  templatesolver.h \
  templateutils.h

LIBS *= -lwikt
LIBS += -L../../../bin
INCLUDEPATH += ../..

