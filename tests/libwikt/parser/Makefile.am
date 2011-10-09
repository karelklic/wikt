TESTS = parsertest
check_PROGRAMS = parsertest
parsertest_SOURCES = parsertest.cpp parsertest.h moc_parsertest.cpp
parsertest_CPPFLAGS = -I../../../src $(QTCORE_CFLAGS) $(QTTEST_CFLAGS)
parsertest_LDFLAGS = $(QTCORE_LDFLAGS) $(QTTEST_LDFLAGS)
parsertest_LDADD = ../../../src/libwikt/libwikt.la $(QTCORE_LIBS) $(QTTEST_LIBS)

moc_%.cpp : %.h
	moc-qt4 -o "$@" "$<"

clean-moc-extra:
	rm -vf moc_*.cpp

clean-local: clean-moc-extra
