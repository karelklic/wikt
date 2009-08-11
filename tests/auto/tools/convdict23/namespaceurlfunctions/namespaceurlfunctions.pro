include(../../../../../wikt.pri)

TEMPLATE=app
QT = core testlib

HEADERS = ../../../../../src/tools/convdict23/namespaceurlfunctions.h

SOURCES += namespaceurlfunctionstest.cpp \
  ../../../../../src/tools/convdict23/namespaceurlfunctions.cpp

LIBS *= -lwikt
LIBS += -L../../../../../bin
INCLUDEPATH +=  ../../../../../src  ../../../../../src/tools/convdict23
