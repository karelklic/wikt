AC_INIT([wikt], [0.20], [kklic@redhat.com])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_ARG_ENABLE(debug,
              [AC_HELP_STRING([--enable-debug],
                             [Enable debug information])],
              [CXXFLAGS="$CXXFLAGS -DDEBUG -ggdb -g"])

AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AC_PROG_CXX
AM_PROG_LEX
AC_PROG_YACC

CXXFLAGS=$CXXFLAGS' -DDATADIR="\"$(pkgdatadir)\""'

PKG_CHECK_MODULES([QTCORE], [QtCore])
PKG_CHECK_MODULES([QTGUI], [QtGui])
PKG_CHECK_MODULES([QTXML], [QtXml])
PKG_CHECK_MODULES([QTWEBKIT], [QtWebKit])
PKG_CHECK_MODULES([QTSVG], [QtSvg])
PKG_CHECK_MODULES([QTTEST], [QtTest])
PKG_CHECK_MODULES([PHONON], [phonon])

LUPDATE=`pkg-config --variable=lupdate_location QtCore`
AC_SUBST(LUPDATE)
if test -z "$LUPDATE"; then
    AC_PATH_PROGS([LUPDATE], [lupdate lupdate-qt4], AC_MSG_ERROR([The lupdate program was not found in the search path.  Please ensure that it is insalled and its directory is included in the serarch path.  Then run configure again before attempting to build Wikt.]))
fi

LRELEASE=`pkg-config --variable=lrelease_location QtCore`
AC_SUBST(LRELEASE)
if test -z "$LRELEASE"; then
    AC_PATH_PROGS([LRELEASE], [lrelease lrelease-qt4], AC_MSG_ERROR([The lrelease program was not found in the search path.  Please ensure that it is insalled and its directory is included in the serarch path.  Then run configure again before attempting to build Wikt.]))
fi

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
	wikt.spec
	Makefile
	translations/Makefile
	src/Makefile
	src/libwikt/Makefile
	src/wikt-dict/Makefile
	src/wikt-gui/Makefile
	tests/Makefile
	tests/libwikt/Makefile
	tests/libwikt/node/Makefile
	tests/libwikt/parser/Makefile
	tests/libwikt/urlutils/Makefile
	tests/wikt-dict/Makefile
])

AC_OUTPUT
