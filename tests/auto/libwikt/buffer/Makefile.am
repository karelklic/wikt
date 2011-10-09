TESTS = buffertest
check_PROGRAMS = buffertest
buffertest_SOURCES = buffertest.cpp buffertest.h moc_buffertest.cpp
buffertest_CPPFLAGS = -I../../../../src $(QTCORE_CFLAGS) $(QTTEST_CFLAGS)
buffertest_LDFLAGS = $(QTCORE_LDFLAGS) $(QTTEST_LDFLAGS)
buffertest_LDADD = ../../../../src/libwikt/libwikt.la $(QTCORE_LIBS) $(QTTEST_LIBS)

moc_%.cpp : %.h
	moc-qt4 -o "$@" "$<"

clean-moc-extra:
	rm -vf moc_*.cpp

clean-local: clean-moc-extra
