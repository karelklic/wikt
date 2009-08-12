include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += urlutilstest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
