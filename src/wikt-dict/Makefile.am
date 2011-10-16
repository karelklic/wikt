bin_PROGRAMS = wikt-dict
wikt_dict_SOURCES = \
	categorybuilder.cpp categorybuilder.h \
	command.h \
	commandmidtodict.cpp \
	commandpreptomid.cpp \
	commandxmltoprep.cpp \
	commanddownloadmedia.cpp \
	commandresizeimages.cpp \
	commandpackmedia.cpp \
	commandsource.cpp \
	exprdriver.cpp exprdriver.h \
	exprscanner.cpp \
	exprparser.tab.cpp exprparser.tab.hpp \
	location.hh position.hh stack.hh \
	format2reader.cpp format2reader.h \
	format3writer.cpp format3writer.h \
	format4writer.cpp format4writer.h \
	formattingfunctions.cpp formattingfunctions.h \
	galleryconverter.cpp galleryconverter.h \
	languagestatistic.cpp languagestatistic.h \
	licensepagesgenerator.cpp licensepagesgenerator.h \
	linkconverter.cpp linkconverter.h \
	main.cpp \
	mediawriter.cpp mediawriter.h \
	namespaceurlfunctions.cpp namespaceurlfunctions.h \
	pagenamefunctions.cpp pagenamefunctions.h \
	parameterlist.cpp parameterlist.h \
	parserfunctions.cpp parserfunctions.h \
	references.cpp references.h \
	statspagegenerator.cpp statspagegenerator.h \
	templatesolver.cpp templatesolver.h \
	templateutils.cpp templateutils.h \
	titlepagegenerator.cpp titlepagegenerator.h

wikt_dict_CPPFLAGS = -I.. $(QTCORE_CFLAGS) $(QTGUI_CFLAGS)
wikt_dict_LDFLAGS = $(QTCORE_LDFLAGS) $(QTGUI_LDFLAGS)
wikt_dict_LDADD = ../libwikt/libwikt.la $(QTCORE_LIBS) $(QTGUI_LIBS)

EXTRA_DIST = exprscanner.lpp exprparser.ypp
AM_YFLAGS = -d
AM_LFLAGS = -d

exprscanner.cpp: exprscanner.lpp
	$(LEX) $(LFLAGS) $(AM_LFLAGS) -o exprscanner.cpp exprscanner.lpp

exprparser.tab.cpp: exprparser.ypp
	bison $(YFLAGS) $(AM_YFLAGS) exprparser.ypp
