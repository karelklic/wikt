include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += listparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
