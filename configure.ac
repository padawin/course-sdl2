#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([SDL2_framework], [0.1], [ghislain.rodrigues@gmail.com])
LT_INIT
AC_CONFIG_SRCDIR([src/Game.cpp])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([SDL2], [SDL_Init], [], [
	echo "SDL2 library is required for this program"
	exit -1])
AC_CHECK_LIB([SDL2_image], [IMG_Load], [], [
	echo "SDL2 Image library is required for this program"
	exit -1])
AC_LANG_CPLUSPLUS
AC_CHECK_LIB(tinyxml, main, [], [
	echo "tinyxml library is required for this program"
	exit -1])
AC_CHECK_LIB([z], [uncompress], [], [
	echo "zip library is required for this program"
	exit -1])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE([subdir-objects])
AC_OUTPUT
