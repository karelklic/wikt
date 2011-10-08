TESTS = urlutilstest
check_PROGRAMS = urlutilstest
urlutilstest_SOURCES = urlutilstest.cpp urlutilstest.h moc_urlutilstest.cpp

urlutilstest_CPPFLAGS = \
  -I../../../../src \
  $(QTCORE_CFLAGS) \
  $(QTTEST_CFLAGS)

urlutilstest_LDFLAGS = \
  $(QTCORE_LDFLAGS) \
  $(QTTEST_LDFLAGS)

urlutilstest_LDADD = \
  ../../../../src/libwikt/libwikt.la \
  $(QTCORE_LIBS) \
  $(QTTEST_LIBS)

moc_%.cpp : %.h
	moc-qt4 -o "$@" "$<"

clean-moc-extra:
	rm -vf moc_*.cpp

clean-local: clean-moc-extra
