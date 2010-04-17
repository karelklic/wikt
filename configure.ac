AC_INIT([wikt], [0.20.0], [kklic@redhat.com])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_ARG_ENABLE(debug,
              [AC_HELP_STRING([--enable-debug],
                             [Enable debug information])],
              [CXXFLAGS="$CXXFLAGS -DDEBUG -ggdb -g"])

AC_DISABLE_STATIC
AC_PROG_LIBTOOL

AC_PROG_CC
CFLAGS=$CFLAGS' -DDATADIR="\"$(pkgdatadir)\""'
AC_PROG_CXX
CXXFLAGS=$CXXFLAGS' -DDATADIR="\"$(pkgdatadir)\""'

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.17])

PKG_CHECK_MODULES([QTCORE], [QtCore])
PKG_CHECK_MODULES([QTGUI], [QtGui])
PKG_CHECK_MODULES([QTXML], [QtXml])
PKG_CHECK_MODULES([QTWEBKIT], [QtWebKit])
PKG_CHECK_MODULES([QTSVG], [QtSvg])
PKG_CHECK_MODULES([PHONON], [phonon])

AC_SUBST(DL_LIBS, -ldl)
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/app/Makefile
	src/libwikt/Makefile
	share/Makefile
	share/data/Makefile
	share/languages/Makefile
	po/Makefile.in
])

AC_OUTPUT
