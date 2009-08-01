TEMPLATE = lib
TARGET = wikt

DEFINES = WIKT_LIBRARY
DESTDIR = ../../bin

QT += core gui xml network svg testlib

HEADERS = \
    debug.h \
    profiler.h \
    profilerview.h \
    comparsion.h \
    fileutils.h \
    format3reader.h \
    format4reader.h \
    mediareader.h \
    mediautils.h \
    options.h \
    prerequisites.h \
    unicode.h \
    urlutils.h \
    version.h \
    namespace.h \
    project.h \
    language.h \
    parser/*.h \
    tree/*.h

SOURCES = \
    debug.cpp \
    profiler.cpp \
    profilerview.cpp \
    fileutils.cpp \
    format3reader.cpp \
    format4reader.cpp \
    mediareader.cpp \
    mediautils.cpp \
    options.cpp \
    unicode.cpp \
    urlutils.cpp \
    namespace.cpp \
    project.cpp \
    language.cpp \
    parser/*.cpp \
    tree/*.cpp
