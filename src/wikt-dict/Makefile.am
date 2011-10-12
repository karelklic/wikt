bin_PROGRAMS = wikt-dict
wikt_dict_SOURCES = \
	command.h \
	commandpreptomid.cpp \
	commandxmltoprep.cpp \
	exprdriver.cpp exprdriver.h \
	exprscanner.cpp \
	exprparser.tab.cpp exprparser.tab.hpp \
	location.hh position.hh stack.hh \
	format2reader.cpp format2reader.h \
	format3writer.cpp format3writer.h \
	formattingfunctions.cpp formattingfunctions.h \
	galleryconverter.cpp galleryconverter.h \
	main.cpp \
	namespaceurlfunctions.cpp namespaceurlfunctions.h \
	pagenamefunctions.cpp pagenamefunctions.h \
	parameterlist.cpp parameterlist.h \
	parserfunctions.cpp parserfunctions.h \
	templatesolver.cpp templatesolver.h \
	templateutils.cpp templateutils.h

wikt_dict_CPPFLAGS = -I.. $(QTCORE_CFLAGS)
wikt_dict_LDFLAGS = $(QTCORE_LDFLAGS)
wikt_dict_LDADD = ../libwikt/libwikt.la $(QTCORE_LIBS)

exprscanner.cpp: exprscanner.l
	flex -d -o exprscanner.cpp exprscanner.l

exprparser.tab.cpp: exprparser.ypp
	bison -d exprparser.ypp
