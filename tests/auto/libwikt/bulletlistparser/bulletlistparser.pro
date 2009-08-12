include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += bulletlistparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
