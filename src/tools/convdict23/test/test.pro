TEMPLATE = app
TARGET = test
QT += testlib

SOURCES += \
  FormattingFunctionsTest.cpp \
  Main.cpp \
  NamespaceUrlFunctionsTest.cpp \
  PageNameFunctionsTest.cpp \
  ParserFunctionsTest.cpp \
  TemplateSolverTest.cpp \
  TemplateUtilsTest.cpp \
  \
  ../ExprParser/ExprDriver.cpp \
  ../ExprParser/ExprParser.tab.cpp \
  ../ExprParser/ExprScanner.cpp \
  ../Format2Reader.cpp \
  ../Format3Writer.cpp \
  ../FormattingFunctions.cpp \
  ../GalleryConverter.cpp \
  ../NamespaceUrlFunctions.cpp \
  ../PageNameFunctions.cpp \
  ../ParameterList.cpp \
  ../ParserFunctions.cpp \
  ../TemplateSolver.cpp \
  ../TemplateUtils.cpp

HEADERS += \
  FormattingFunctionsTest.h \
  NamespaceUrlFunctionsTest.h \
  PageNameFunctionsTest.h \
  ParserFunctionsTest.h \
  TemplateSolverTest.h \
  TemplateUtilsTest.h \
  \
  ../ExprParser/ExprDriver.h \
  ../ExprParser/ExprParser.tab.hpp \
  ../ExprParser/location.hh \
  ../ExprParser/position.hh \
  ../ExprParser/stack.hh \
  ../Format2Reader.h \
  ../Format3Writer.h \
  ../FormattingFunctions.h \
  ../GalleryConverter.h \
  ../NamespaceUrlFunctions.h \
  ../PageNameFunctions.h \
  ../ParameterList.h \
  ../ParserFunctions.h \
  ../TemplateSolver.h \
  ../TemplateUtils.h

LIBS *= -lwikt
LIBPATH *= ../../../../bin
INCLUDEPATH += ../../..

