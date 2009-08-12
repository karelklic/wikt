include(../../../../../wikt.pri)

TEMPLATE=app
QT = core testlib

HEADERS = ../../../../../src/tools/convdict34/linkconverter.h

SOURCES += linkconvertertest.cpp \
  ../../../../../src/tools/convdict34/linkconverter.cpp

LIBS *= -lwikt
LIBS += -L../../../../../bin
INCLUDEPATH +=  ../../../../../src  ../../../../../src/tools/convdict34
