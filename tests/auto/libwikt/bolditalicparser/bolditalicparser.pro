include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += bolditalicparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
