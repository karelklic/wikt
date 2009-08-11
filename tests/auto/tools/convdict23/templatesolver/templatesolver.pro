include(../../../../../wikt.pri)

TEMPLATE=app
QT = core testlib

HEADERS = \
  ../../../../../src/tools/convdict23/templatesolver.h \
  ../../../../../src/tools/convdict23/parserfunctions.h \
  ../../../../../src/tools/convdict23/exprparser/exprdriver.h \
  ../../../../../src/tools/convdict23/format2reader.h \
  ../../../../../src/tools/convdict23/templateutils.h \
  ../../../../../src/tools/convdict23/parameterlist.h \
  ../../../../../src/tools/convdict23/formattingfunctions.h \
  ../../../../../src/tools/convdict23/pagenamefunctions.h \
  ../../../../../src/tools/convdict23/namespaceurlfunctions.h

SOURCES += templatesolvertest.cpp \
  ../../../../../src/tools/convdict23/templatesolver.cpp \
  ../../../../../src/tools/convdict23/parserfunctions.cpp \
  ../../../../../src/tools/convdict23/exprparser/exprdriver.cpp \
  ../../../../../src/tools/convdict23/exprparser/exprparser.tab.cpp \
  ../../../../../src/tools/convdict23/exprparser/exprscanner.cpp \
  ../../../../../src/tools/convdict23/format2reader.cpp \
  ../../../../../src/tools/convdict23/templateutils.cpp \
  ../../../../../src/tools/convdict23/parameterlist.cpp \
  ../../../../../src/tools/convdict23/formattingfunctions.cpp \
  ../../../../../src/tools/convdict23/pagenamefunctions.cpp \
  ../../../../../src/tools/convdict23/namespaceurlfunctions.cpp

LIBS *= -lwikt
LIBS += -L../../../../../bin
INCLUDEPATH +=  ../../../../../src  ../../../../../src/tools/convdict23
