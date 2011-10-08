noinst_LIBRARIES = libexprparser.a
libexprparser_a_SOURCES = \
  exprdriver.cpp exprdriver.h \
  exprscanner.cpp \
  exprparser.tab.cpp exprparser.tab.hpp \
  location.hh position.hh stack.hh

libexprparser_a_CPPFLAGS = -I../../.. -I../.. $(QTCORE_CFLAGS)

exprscanner.cpp: exprscanner.l
	flex -d -o exprscanner.cpp exprscanner.l

exprparser.tab.cpp: exprparser.ypp
	bison -d exprparser.ypp
