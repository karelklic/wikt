include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += tablecellparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
