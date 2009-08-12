include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += paragraphparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
