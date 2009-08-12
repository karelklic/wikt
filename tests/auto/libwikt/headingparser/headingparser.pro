include(../../../../wikt.pri)

TEMPLATE = app
QT = core testlib
SOURCES += headingparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
