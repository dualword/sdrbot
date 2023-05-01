dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(sdrbot-desktop, 1.0)

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CXXCPP
AC_PROG_CXX

QT_PATH=/usr/include/qt4

QT_CXXFLAGS=" -I$QT_PATH -I$QT_PATH/QtCore -I$QT_PATH/QtGui"
QT_LIBS="-lQtCore -lQtGui"
LIBS="$QT_LIBS"

CXXFLAGS=" $QT_CXXFLAGS -std=c++0x"

AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])
AC_SUBST([LIBS])

AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT
