include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += tableparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
