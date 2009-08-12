include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += articlenodetest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
