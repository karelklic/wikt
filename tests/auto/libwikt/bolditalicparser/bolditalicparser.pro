include(../../../../wikt.pri)

TEMPLATE=app
QT = core testlib
SOURCES += bparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
