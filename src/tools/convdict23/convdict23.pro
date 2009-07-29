TEMPLATE = app
TARGET = convdict23

SOURCES += \
  ExprParser/ExprDriver.cpp \
  ExprParser/ExprParser.tab.cpp \
  ExprParser/ExprScanner.cpp \
  Format2Reader.cpp \
  Format3Writer.cpp \
  FormattingFunctions.cpp \
  GalleryConverter.cpp \
  Main.cpp \
  NamespaceUrlFunctions.cpp \
  PageNameFunctions.cpp \
  ParameterList.cpp \
  ParserFunctions.cpp \
  TemplateSolver.cpp \
  TemplateUtils.cpp

HEADERS += \
  ExprParser/ExprDriver.h \
  ExprParser/ExprParser.tab.hpp \
  ExprParser/location.hh \
  ExprParser/position.hh \
  ExprParser/stack.hh \
  Format2Reader.h \
  Format3Writer.h \
  FormattingFunctions.h \
  GalleryConverter.h \
  NamespaceUrlFunctions.h \
  PageNameFunctions.h \
  ParameterList.h \
  ParserFunctions.h \
  TemplateSolver.h \
  TemplateUtils.h

LIBS *= -lwikt
LIBS += -L../../../bin

INCLUDEPATH += ../../lib
DESTDIR = ../../../bin
