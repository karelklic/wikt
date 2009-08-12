include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += inlinehtmlparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
