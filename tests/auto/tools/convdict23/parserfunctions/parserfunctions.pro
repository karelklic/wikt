include(../../../../../wikt.pri)

TEMPLATE=app
QT = core testlib

HEADERS = \
  ../../../../../src/tools/convdict23/parserfunctions.h \
  ../../../../../src/tools/convdict23/exprparser/exprdriver.h \
  ../../../../../src/tools/convdict23/format2reader.h \
  ../../../../../src/tools/convdict23/templateutils.h \
  ../../../../../src/tools/convdict23/parameterlist.h

SOURCES += parserfunctionstest.cpp \
  ../../../../../src/tools/convdict23/parserfunctions.cpp \
  ../../../../../src/tools/convdict23/exprparser/exprdriver.cpp \
  ../../../../../src/tools/convdict23/exprparser/exprparser.tab.cpp \
  ../../../../../src/tools/convdict23/exprparser/exprscanner.cpp \
  ../../../../../src/tools/convdict23/format2reader.cpp \
  ../../../../../src/tools/convdict23/templateutils.cpp \
  ../../../../../src/tools/convdict23/parameterlist.cpp

LIBS *= -lwikt
LIBS += -L../../../../../bin
INCLUDEPATH +=  ../../../../../src  ../../../../../src/tools/convdict23
