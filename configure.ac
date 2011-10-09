AC_INIT([wikt], [0.20.0], [kklic@redhat.com])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_ARG_ENABLE(debug,
              [AC_HELP_STRING([--enable-debug],
                             [Enable debug information])],
              [CXXFLAGS="$CXXFLAGS -DDEBUG -ggdb -g"])

AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AC_PROG_CXX

CXXFLAGS=$CXXFLAGS' -DDATADIR="\"$(pkgdatadir)\""'

PKG_CHECK_MODULES([QTCORE], [QtCore])
PKG_CHECK_MODULES([QTGUI], [QtGui])
PKG_CHECK_MODULES([QTXML], [QtXml])
PKG_CHECK_MODULES([QTWEBKIT], [QtWebKit])
PKG_CHECK_MODULES([QTSVG], [QtSvg])
PKG_CHECK_MODULES([QTTEST], [QtTest])
PKG_CHECK_MODULES([PHONON], [phonon])

AC_SUBST(DL_LIBS, -ldl)
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
	Makefile
	share/Makefile
	share/wikt/Makefile
	share/wikt/translations/Makefile
	src/Makefile
	src/app/Makefile
	src/libwikt/Makefile
	src/tools/Makefile
	src/tools/convdict12/Makefile
	src/tools/convdict23/Makefile
	src/tools/convdict23/exprparser/Makefile
	src/tools/convdict34/Makefile
	src/tools/dict3src/Makefile
	src/tools/dict4src/Makefile
	src/tools/imageresizer/Makefile
	src/tools/mediadownloader/Makefile
	src/tools/mediapacker/Makefile
	src/tools/wikitoxml/Makefile
	tests/Makefile
	tests/auto/Makefile
	tests/auto/libwikt/Makefile
	tests/auto/libwikt/buffer/Makefile
	tests/auto/libwikt/node/Makefile
	tests/auto/libwikt/parser/Makefile
	tests/auto/libwikt/urlutils/Makefile
])

AC_OUTPUT
