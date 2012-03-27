AC_INIT([fuzzyclock], [0.1], [github@caioromao.com])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_PROG_CC
AC_PROG_RANLIB

AM_PROG_CC_C_O
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])

AC_OUTPUT
