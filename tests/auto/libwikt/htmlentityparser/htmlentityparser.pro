include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += htmlentityparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
