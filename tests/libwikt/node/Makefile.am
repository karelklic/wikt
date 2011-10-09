TESTS = nodetest
check_PROGRAMS = nodetest
nodetest_SOURCES = nodetest.cpp nodetest.h moc_nodetest.cpp
nodetest_CPPFLAGS = -I../../../src $(QTCORE_CFLAGS) $(QTTEST_CFLAGS)
nodetest_LDFLAGS = $(QTCORE_LDFLAGS) $(QTTEST_LDFLAGS)
nodetest_LDADD = ../../../src/libwikt/libwikt.la $(QTCORE_LIBS) $(QTTEST_LIBS)

moc_%.cpp : %.h
	moc-qt4 -o "$@" "$<"

clean-moc-extra:
	rm -vf moc_*.cpp

clean-local: clean-moc-extra
