include(../../../../wikt.pri)

TEMPLATE=app
QT = core testlib
SOURCES += blockhtmlparsertest.cpp

LIBS *= -lwikt
LIBS += -L../../../../bin
INCLUDEPATH += ../../../../src
