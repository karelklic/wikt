TESTS = commandpreptomidtest commandmidtodicttest
check_PROGRAMS = commandpreptomidtest commandmidtodicttest
commandpreptomidtest_SOURCES = \
	commandpreptomidtest.cpp commandpreptomidtest.h \
	moc_commandpreptomidtest.cpp \
	../../src/wikt-dict/formattingfunctions.cpp \
	../../src/wikt-dict/formattingfunctions.h \
	../../src/wikt-dict/namespaceurlfunctions.cpp \
	../../src/wikt-dict/namespaceurlfunctions.h \
	../../src/wikt-dict/pagenamefunctions.cpp \
	../../src/wikt-dict/pagenamefunctions.h \
	../../src/wikt-dict/parserfunctions.cpp \
	../../src/wikt-dict/parserfunctions.h \
	../../src/wikt-dict/exprdriver.cpp \
	../../src/wikt-dict/exprdriver.h \
	../../src/wikt-dict/exprparser.tab.cpp \
	../../src/wikt-dict/exprscanner.cpp \
	../../src/wikt-dict/format2reader.cpp \
	../../src/wikt-dict/format2reader.h \
	../../src/wikt-dict/templatesolver.cpp \
	../../src/wikt-dict/templatesolver.h \
	../../src/wikt-dict/templateutils.cpp \
	../../src/wikt-dict/templateutils.h \
	../../src/wikt-dict/parameterlist.cpp \
	../../src/wikt-dict/parameterlist.h

commandpreptomidtest_CPPFLAGS = -I../../src \
	-I ../../src/wikt-dict \
	$(QTCORE_CFLAGS) $(QTTEST_CFLAGS)

commandpreptomidtest_LDFLAGS = $(QTCORE_LDFLAGS) $(QTTEST_LDFLAGS)
commandpreptomidtest_LDADD = ../../src/libwikt/libwikt.la $(QTCORE_LIBS) $(QTTEST_LIBS)

commandmidtodicttest_SOURCES = \
	commandmidtodicttest.cpp commandmidtodicttest.h \
	moc_commandmidtodicttest.cpp \
	../../src/wikt-dict/linkconverter.cpp \
	../../src/wikt-dict/linkconverter.h

commandmidtodicttest_CPPFLAGS = -I../../src \
	-I ../../src/wikt-dict \
	$(QTCORE_CFLAGS) $(QTTEST_CFLAGS)

commandmidtodicttest_LDFLAGS = $(QTCORE_LDFLAGS) $(QTTEST_LDFLAGS)
commandmidtodicttest_LDADD = ../../src/libwikt/libwikt.la $(QTCORE_LIBS) $(QTTEST_LIBS)

moc_%.cpp : %.h
	moc-qt4 -o "$@" "$<"

clean-moc-extra:
	rm -vf moc_*.cpp

clean-local: clean-moc-extra
