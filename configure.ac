AC_PREREQ([2.69])

# ------------------------------------------------------------------------------
# Package setup
# ------------------------------------------------------------------------------
AC_INIT([cern_test], [0.1.0], [iacopobreschi])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
INSTALL="${INSTALL} -C"

# ------------------------------------------------------------------------------
# Default flag reinitialization
# ------------------------------------------------------------------------------
CXXFLAGS="-Wall -Wextra ${CXXFLAGS}"
CFLAGS="-Wall -Wextra ${CFLAGS}"

if test x"$CFLAGS" = x""; then
  AC_SUBST(CFLAGS, [ ])
fi
if test x"$CXXFLAGS" = x""; then
  AC_SUBST(CXXFLAGS, [ ])
fi
# ------------------------------------------------------------------------------
# Check for tool support
# ------------------------------------------------------------------------------
AC_PROG_CXX
AC_PROG_LIBTOOL
AM_PROG_CC_C_O

# ------------------------------------------------------------------------------
# Check for C++ support
# ------------------------------------------------------------------------------
AC_LANG([C++])

# ------------------------------------------------------------------------------
# Enable silent build rules by default
# ------------------------------------------------------------------------------
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])],[AC_SUBST([AM_DEFAULT_VERBOSITY], [1])])

# ------------------------------------------------------------------------------
# Check for boost-system library
# ------------------------------------------------------------------------------
AX_BOOST_BASE([1.40.0],[],
	[AC_MSG_ERROR([Boost headers are needed to build this library.
	Please go to www.boost.org to download them.])]
)
AX_BOOST_SYSTEM
AX_BOOST_THREAD
# ------------------------------------------------------------------------------
# Check for pthread libraries
# ------------------------------------------------------------------------------
ACX_PTHREAD([have_pthread=yes])


# ------------------------------------------------------------------------------
# Check for C++ libraries
# ------------------------------------------------------------------------------

AC_CHECK_HEADERS([cstddef iostream limits memory  sstream  string vector], [],
   [AC_MSG_ERROR([missing standard C++ header])])

# ---------------------------------------------------------------------
# Enable options
# ---------------------------------------------------------------------
AC_ARG_ENABLE( [debug],
	AS_HELP_STRING([--enable-debug],
	[compile with debug symbols @<:@default=no@:>@]),
    [want_debug="$enableval"], [want_debug=no])
# ---------------------------------------------------------------------
# Debug and profile
# ---------------------------------------------------------------------

if test "x$want_debug" = "xyes"; then
    CFLAGS="$CFLAGS -g3 -O0 -Wall"
	CXXFLAGS="$CXXFLAGS -g3 -O0 -Wall"
else
  CFLAGS="$CFLAGS -O2"
  CXXFLAGS="$CXXFLAGS -O2"
fi


AC_TYPE_SIZE_T

# ------------------------------------------------------------------------------
# Declare output files
# ------------------------------------------------------------------------------
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT

AC_MSG_RESULT([
cern_test-autotools is now configured
Configure Information:
  C++ Compiler      : $CXX
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CXXFLAGS        :   $CXXFLAGS

  Linker            : $LD
    LDFLAGS         :   $LDFLAGS
    LIBS            :   $LIBS

])