include(../../../../../wikt.pri)

TEMPLATE=app
QT = core testlib

HEADERS = \
  ../../../../../src/tools/convdict23/templateutils.h \
  ../../../../../src/tools/convdict23/parameterlist.h

SOURCES += templateutilstest.cpp \
  ../../../../../src/tools/convdict23/templateutils.cpp \
  ../../../../../src/tools/convdict23/parameterlist.cpp

LIBS *= -lwikt
LIBS += -L../../../../../bin
INCLUDEPATH +=  ../../../../../src  ../../../../../src/tools/convdict23
