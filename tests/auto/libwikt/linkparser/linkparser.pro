include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += linkparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
