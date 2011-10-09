TESTS = convdict23test
check_PROGRAMS = convdict23test
convdict23test_SOURCES = \
	convdict23test.cpp convdict23test.h moc_convdict23test.cpp \
	../../../src/tools/convdict23/formattingfunctions.cpp \
	../../../src/tools/convdict23/formattingfunctions.h \
	../../../src/tools/convdict23/namespaceurlfunctions.cpp \
	../../../src/tools/convdict23/namespaceurlfunctions.h \
	../../../src/tools/convdict23/pagenamefunctions.cpp \
	../../../src/tools/convdict23/pagenamefunctions.h \
	../../../src/tools/convdict23/parserfunctions.cpp \
	../../../src/tools/convdict23/parserfunctions.h \
	../../../src/tools/convdict23/exprparser/exprdriver.cpp \
	../../../src/tools/convdict23/exprparser/exprdriver.h \
	../../../src/tools/convdict23/exprparser/exprparser.tab.cpp \
	../../../src/tools/convdict23/exprparser/exprscanner.cpp \
	../../../src/tools/convdict23/format2reader.cpp \
	../../../src/tools/convdict23/format2reader.h \
	../../../src/tools/convdict23/templatesolver.cpp \
	../../../src/tools/convdict23/templatesolver.h \
	../../../src/tools/convdict23/templateutils.cpp \
	../../../src/tools/convdict23/templateutils.h \
	../../../src/tools/convdict23/parameterlist.cpp \
	../../../src/tools/convdict23/parameterlist.h

convdict23test_CPPFLAGS = -I../../../src \
	-I ../../../src/tools/convdict23 \
	$(QTCORE_CFLAGS) $(QTTEST_CFLAGS)

convdict23test_LDFLAGS = $(QTCORE_LDFLAGS) $(QTTEST_LDFLAGS)
convdict23test_LDADD = ../../../src/libwikt/libwikt.la $(QTCORE_LIBS) $(QTTEST_LIBS)

moc_%.cpp : %.h
	moc-qt4 -o "$@" "$<"

clean-moc-extra:
	rm -vf moc_*.cpp

clean-local: clean-moc-extra
