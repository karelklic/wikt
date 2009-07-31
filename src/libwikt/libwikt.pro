TEMPLATE = lib
TARGET = wikt

DEFINES = WIKT_LIBRARY
DESTDIR = ../../bin

QT += core \
    gui \
    xml \
    network \
    svg \
    testlib

HEADERS = \
    Parser/TableCaptionParser.h \
    Debug.h \
    Profiler.h \
    ProfilerView.h \
    Comparsion.h \
    FileUtils.h \
    Format3Reader.h \
    Format4Reader.h \
    MediaReader.h \
    MediaUtils.h \
    getopt.h \
    Prerequisites.h \
    Unicode.h \
    UrlUtils.h \
    Version.h \
    Namespace.h \
    Project.h \
    Language.h \
    Parser/*.h \
    Tree/*.h

SOURCES = \
    Debug.cpp \
    Profiler.cpp \
    ProfilerView.cpp \
    FileUtils.cpp \
    Format3Reader.cpp \
    Format4Reader.cpp \
    MediaReader.cpp \
    MediaUtils.cpp \
    getopt.cpp \
    Unicode.cpp \
    UrlUtils.cpp \
    Namespace.cpp \
    Project.cpp \
    Language.cpp \
    Parser/*.cpp \
    Tree/*.cpp
