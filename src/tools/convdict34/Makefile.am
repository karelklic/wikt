bin_PROGRAMS = convdict34

convdict34_SOURCES = \
  categorybuilder.cpp categorybuilder.h \
  format4writer.cpp format4writer.h \
  languagestatistic.cpp languagestatistic.h \
  licensepagesgenerator.cpp licensepagesgenerator.h \
  linkconverter.cpp linkconverter.h \
  main.cpp \
  references.cpp references.h \
  statspagegenerator.cpp statspagegenerator.h \
  titlepagegenerator.cpp titlepagegenerator.h

convdict34_CPPFLAGS = -I../.. $(QTCORE_CFLAGS)

convdict34_LDFLAGS = $(QTCORE_LDFLAGS)

convdict34_LDADD = ../../libwikt/libwikt.la $(QTCORE_LIBS)
