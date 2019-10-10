AC_INIT([murrayc-tuple-utils],[0.0.3])
AC_PREREQ(2.63)

AC_CONFIG_SRCDIR([tests/test_tuple_cdr.cc])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([macros])
$AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.10 -Wno-portability no-define nostdinc tar-ustar])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX

AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])

LT_PREREQ([2.2.6])
LT_INIT([win32-dll])

MM_PREREQ([0.9.5])
MM_INIT_MODULE([murrayc-tuple-utils-1.0])

# Tell mm-common-prepare to copy the mm-common .pl scripts
# and some other files into docs/, and use them from there,
# so we can dist them to avoid a tarball-build dependency.
MM_CONFIG_DOCTOOL_DIR([docs])

MM_ARG_ENABLE_DOCUMENTATION
#For instance: MM_ARG_WITH_TAGFILE_DOC([libstdc++.tag], [mm-common-libstdc++])

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([LIBMURRAYC_TUPLE_UTILS_SO_VERSION], [0:0:0])

PKG_CHECK_MODULES([PROJECT_TESTS], [gtest_main])

AC_LANG([C++])
MM_ARG_ENABLE_WARNINGS([PROJECT_WXXFLAGS],
                       [-Wall],
                       [-pedantic -Wall -Wextra -Wsuggest-override -Wshadow -Wformat-security -Wno-missing-field-initializers -fsanitize=undefined -ftrapv -DGSEAL_ENABLE],
                       [])


# TODO: Just use the regular PREFIXSUFFIX_WXXFLAG
# (and use -I instead of -isystem in Makefile_tes
# if this googletest problem is fixed:
# https://github.com/google/googletest/issues/533
MM_ARG_ENABLE_WARNINGS([PROJECT_GTEST_WXXFLAGS],
                       [-Wall],
                       [-pedantic -Wall -Wextra -Wshadow -Wformat-security -Wno-missing-field-initializers -fsanitize=undefined -ftrapv -DGSEAL_ENABLE],
                       [])

AC_CONFIG_FILES([Makefile
  ${MURRAYC_TUPLE_UTILS_MODULE_NAME}.pc:murrayc-tuple-utils.pc.in
  docs/Makefile
  docs/reference/Doxyfile])

AC_OUTPUT
