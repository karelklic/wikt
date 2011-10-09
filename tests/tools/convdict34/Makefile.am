TESTS = convdict34test
check_PROGRAMS = convdict34test
convdict34test_SOURCES = \
	convdict34test.cpp convdict34test.h moc_convdict34test.cpp \
	../../../src/tools/convdict34/linkconverter.cpp \
	../../../src/tools/convdict34/linkconverter.h

convdict34test_CPPFLAGS = -I../../../src \
	-I ../../../src/tools/convdict34 \
	$(QTCORE_CFLAGS) $(QTTEST_CFLAGS)

convdict34test_LDFLAGS = $(QTCORE_LDFLAGS) $(QTTEST_LDFLAGS)
convdict34test_LDADD = ../../../src/libwikt/libwikt.la $(QTCORE_LIBS) $(QTTEST_LIBS)

moc_%.cpp : %.h
	moc-qt4 -o "$@" "$<"

clean-moc-extra:
	rm -vf moc_*.cpp

clean-local: clean-moc-extra
