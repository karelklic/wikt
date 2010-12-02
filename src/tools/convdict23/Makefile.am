SUBDIRS = exprparser

bin_PROGRAMS = convdict23

convdict23_SOURCES = \
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

convdict23_CPPFLAGS = -I../.. $(QTCORE_CFLAGS)

convdict23_LDFLAGS = $(QTCORE_LDFLAGS)

convdict23_LDADD = \
  ../../libwikt/libwikt.la \
  exprparser/libexprparser.a \
  $(QTCORE_LIBS)
