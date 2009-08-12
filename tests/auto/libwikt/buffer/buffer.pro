include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += buffertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
