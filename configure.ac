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
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.17])
PKG_CHECK_MODULES([QT], [QtCore >= 4.4.0 QtGui >= 4.4.0 QtXml >= 4.4.0])

AC_SUBST(DL_LIBS, -ldl)
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
	Makefile
])

AC_OUTPUT
