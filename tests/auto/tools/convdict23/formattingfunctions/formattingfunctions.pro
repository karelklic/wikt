include(../../../../../wikt.pri)

TEMPLATE=app
QT = core testlib

HEADERS = ../../../../../src/tools/convdict23/formattingfunctions.h

SOURCES += formattingfunctionstest.cpp \
  ../../../../../src/tools/convdict23/formattingfunctions.cpp

LIBS *= -lwikt
LIBS += -L../../../../../bin
INCLUDEPATH +=  ../../../../../src  ../../../../../src/tools/convdict23
