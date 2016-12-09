# Put compiled object files into the same sub-directory as their sources
AUTOMAKE_OPTIONS = subdir-objects

# Point to our macro directory and pick up user flags from the environment
ACLOCAL_AMFLAGS  = -I macros ${ACLOCAL_FLAGS}

# Make warnings always fatal at distcheck time, and disable execution
# of tools that change files not installed by the package itself
DISTCHECK_CONFIGURE_FLAGS = --enable-warnings=fatal --disable-update-mime-database

if ENABLE_DOCUMENTATION
doc_subdirs = docs
else
doc_subdirs =
endif

SUBDIRS = $(doc_subdirs)

dist_noinst_SCRIPTS = autogen.sh

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = $(MURRAYC_TUPLE_UTILS_MODULE_NAME).pc

# Put the CMake build files in the tarball created by autotools' "make distcheck".
dist_noinst_DATA = CMakeLists.txt \
		   cmake_uninstall.cmake.in \
		   tests/CMakeLists.txt

include $(top_srcdir)/tuple-utils/filelist.am

lib_LTLIBRARIES = libmurrayc-tuple-utils-@MURRAYC_TUPLE_UTILS_API_VERSION@.la
libmurrayc_tuple_utils_@MURRAYC_TUPLE_UTILS_API_VERSION@_la_SOURCES = $(cc_sources) $(h_sources_public)
libmurrayc_tuple_utils_@MURRAYC_TUPLE_UTILS_API_VERSION@_la_LDFLAGS = -no-undefined -version-info $(LIBMURRAYC_TUPLE_UTILS_SO_VERSION)
#libmurrayc_tuple_utils_@MURRAYC_TUPLE_UTILS_API_VERSION@_la_LIBADD = $(LIBXMLXX_LIBS)

library_includedir = $(includedir)/$(MURRAYC_TUPLE_UTILS_MODULE_NAME)
nobase_library_include_HEADERS = $(h_sources_public)


# Build googletest:
gtest_top = googletest/googletest
check_LTLIBRARIES = libgtest.la
libgtest_la_SOURCES = googletest/googletest/src/gtest-all.cc \
		      googletest/googletest/src/gtest_main.cc

libgtest_la_CPPFLAGS = -I$(top_srcdir)/$(gtest_top)/include -I$(top_srcdir)/$(gtest_top) \
		       $(PROJECT_GTEST_WXXFLAGS)
libgtest_la_LDFLAGS = -pthread
EXTRA_DIST = $(gtest_top)/src/gtest-all.cc \
	     $(gtest_top)/src/gtest-filepath.cc \
	     $(gtest_top)/src/gtest-printers.cc \
	     $(gtest_top)/src/gtest.cc \
	     $(gtest_top)/src/gtest_main.cc \
	     $(gtest_top)/src/gtest-test-part.cc \
	     $(gtest_top)/src/gtest-death-test.cc \
	     $(gtest_top)/src/gtest-port.cc \
	     $(gtest_top)/src/gtest-typed-test.cc \
	     $(gtest_top)/src/gtest-internal-inl.h \
	     $(gtest_top)/include/gtest/gtest-death-test.h \
	     $(gtest_top)/include/gtest/gtest_pred_impl.h \
	     $(gtest_top)/include/gtest/gtest-test-part.h \
	     $(gtest_top)/include/gtest/gtest.h \
	     $(gtest_top)/include/gtest/gtest-printers.h \
	     $(gtest_top)/include/gtest/gtest-typed-test.h \
	     $(gtest_top)/include/gtest/gtest-message.h \
	     $(gtest_top)/include/gtest/gtest_prod.h \
	     $(gtest_top)/include/gtest/gtest-param-test.h \
	     $(gtest_top)/include/gtest/gtest-spi.h \
	     $(gtest_top)/include/gtest/internal/gtest-death-test-internal.h \
	     $(gtest_top)/include/gtest/internal/gtest-port-arch.h \
	     $(gtest_top)/include/gtest/internal/gtest-filepath.h \
	     $(gtest_top)/include/gtest/internal/gtest-port.h \
	     $(gtest_top)/include/gtest/internal/gtest-internal.h \
	     $(gtest_top)/include/gtest/internal/gtest-string.h \
	     $(gtest_top)/include/gtest/internal/gtest-linked_ptr.h \
	     $(gtest_top)/include/gtest/internal/gtest-tuple.h \
	     $(gtest_top)/include/gtest/internal/gtest-param-util-generated.h \
	     $(gtest_top)/include/gtest/internal/gtest-type-util.h \
	     $(gtest_top)/include/gtest/internal/gtest-param-util.h \
	     $(gtest_top)/include/gtest/internal/custom/gtest.h \
	     $(gtest_top)/include/gtest/internal/custom/gtest-printers.h \
	     $(gtest_top)/include/gtest/internal/custom/gtest-port.h

COMMON_CXXFLAGS = $(PROJECT_CFLAGS) $(PROJECT_WXXFLAGS) $(BOOST_CPPFLAGS)
COMMON_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir) \
		  -isystem $(top_srcdir)/$(gtest_top)/include
COMMON_LIBS = $(PROJECT_LIBS) libgtest.la

check_PROGRAMS = \
  tests/test_tuple_cat \
  tests/test_tuple_cdr \
  tests/test_tuple_end \
  tests/test_tuple_for_each \
  tests/test_tuple_interlace \
  tests/test_tuple_print \
  tests/test_tuple_start \
  tests/test_tuple_subset \
  tests/test_tuple_transform_each

TESTS = $(check_PROGRAMS)

#List of source files needed to build the executable:

tests_test_tuple_cat_SOURCES = \
	tests/test_tuple_cat.cc
tests_test_tuple_cat_CPPFLAGS = \
	$(COMMON_CPPFLAGS)
tests_test_tuple_cat_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_cat_LDADD = \
	$(COMMON_LIBS)

tests_test_tuple_cdr_SOURCES = \
	tests/test_tuple_cdr.cc
tests_test_tuple_cdr_CPPFLAGS = \
	$(COMMON_CPPFLAGS)
tests_test_tuple_cdr_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_cdr_LDADD = \
	$(COMMON_LIBS)

tests_test_tuple_end_SOURCES = \
	tests/test_tuple_end.cc
tests_test_tuple_end_CPPFLAGS = \
	$(COMMON_CPPFLAGS)
tests_test_tuple_end_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_end_LDADD = \
	$(COMMON_LIBS)

tests_test_tuple_for_each_SOURCES = \
	tests/test_tuple_for_each.cc
tests_test_tuple_for_each_CPPFLAGS = \
	$(COMMON_CPPFLAGS)
tests_test_tuple_for_each_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_for_each_LDADD = \
	$(COMMON_LIBS)

tests_test_tuple_interlace_SOURCES = \
	tests/test_tuple_interlace.cc
tests_test_tuple_interlace_CPPFLAGS = \
	$(COMMON_CPPFLAGS)
tests_test_tuple_interlace_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_interlace_LDADD = \
	$(COMMON_LIBS)

tests_test_tuple_print_SOURCES = \
	tests/test_tuple_print.cc
tests_test_tuple_print_CPPFLAGS = \
	$(COMMON_CPPFLAGS)
tests_test_tuple_print_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_print_LDADD = \
	$(COMMON_LIBS)

tests_test_tuple_start_SOURCES = \
	tests/test_tuple_start.cc
tests_test_tuple_start_CPPFLAGS = \
	$(COMMON_CPPFLAGS)
tests_test_tuple_start_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_start_LDADD = \
	$(COMMON_LIBS)

tests_test_tuple_subset_SOURCES = \
	tests/test_tuple_subset.cc
tests_test_tuple_subset_CPPFLAGS = \
	$(COMMON_CPPFLAGS)
tests_test_tuple_subset_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_subset_LDADD = \
	$(COMMON_LIBS)

tests_test_tuple_transform_each_SOURCES = \
	tests/test_tuple_transform_each.cc
tests_test_tuple_transform_each_CPPFLAGS = \
	$(COMMON_CPPFLAGS)
tests_test_tuple_transform_each_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_transform_each_LDADD = \
	$(COMMON_LIBS)



CLEANFILES = stamp-h2

