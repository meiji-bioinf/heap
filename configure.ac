#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT(heap, 0.78, mcova@meiji.ac.jp)
AM_INIT_AUTOMAKE(heap, 0.7.8, no-define)
AC_CONFIG_SRCDIR([heap.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
cxxflags_save="$CXXFLAGS"
AC_PROG_CXX
CXXFLAGS="$cxxflags_save"
test -n "$CXXFLAGS" || CXXFLAGS="-g -Wall -O3"

# Checks for libraries.
LIBS="-lboost_system -lboost_thread-mt -lboost_program_options -lhts"

# Checks for header files.
AC_CHECK_HEADERS([iostream])
AC_CHECK_HEADERS([string])
AC_CHECK_HEADERS([sstream])
AC_CHECK_HEADERS([fstream])
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stlib.h])
AC_CHECK_HEADERS([vector])
AC_CHECK_HEADERS([boost/algorithm/string.hpp])
AC_CHECK_HEADERS([boost/tr1/unordered_map.hpp])
AC_CHECK_HEADERS([boost/thread.hpp])
AC_CHECK_HEADERS([boost/bind.hpp])
AC_CHECK_HEADERS([boost/program_options.hpp])
AC_CHECK_HEADERS([bam.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
