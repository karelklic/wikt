include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += textblockparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
