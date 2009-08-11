include(../../../../../wikt.pri)

TEMPLATE=app
QT = core testlib

HEADERS = ../../../../../src/tools/convdict23/pagenamefunctions.h

SOURCES += pagenamefunctionstest.cpp \
  ../../../../../src/tools/convdict23/pagenamefunctions.cpp

LIBS *= -lwikt
LIBS += -L../../../../../bin
INCLUDEPATH +=  ../../../../../src  ../../../../../src/tools/convdict23
