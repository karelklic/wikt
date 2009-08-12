include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += numberedlistparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
