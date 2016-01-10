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

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = $(MURRAYC_TUPLE_UTILS_MODULE_NAME).pc

AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)
AM_CXXFLAGS = $(PROJECT_WXXFLAGS)

# TODO: Why do we still need to specify this for each executable that we build?
COMMON_CXXFLAGS = $(PROJECT_CFLAGS) $(PROJECT_WXXFLAGS) $(BOOST_CPPFLAGS)

include $(top_srcdir)/tuple-utils/filelist.am

lib_LTLIBRARIES = libmurrayc-tuple-utils-@MURRAYC_TUPLE_UTILS_API_VERSION@.la
libmurrayc_tuple_utils_@MURRAYC_TUPLE_UTILS_API_VERSION@_la_SOURCES = $(cc_sources) $(h_sources_public)
libmurrayc_tuple_utils_@MURRAYC_TUPLE_UTILS_API_VERSION@_la_LDFLAGS = -no-undefined -version-info $(LIBMURRAYC_TUPLE_UTILS_SO_VERSION)
#libmurrayc_tuple_utils_@MURRAYC_TUPLE_UTILS_API_VERSION@_la_LIBADD = $(LIBXMLXX_LIBS)

library_includedir = $(includedir)/$(MURRAYC_TUPLE_UTILS_MODULE_NAME)
nobase_library_include_HEADERS = $(h_sources_public)


check_PROGRAMS = \
  tests/test_tuple_cat \
  tests/test_tuple_cdr \
  tests/test_tuple_end \
  tests/test_tuple_interlace \
  tests/test_tuple_start \
  tests/test_tuple_subset \
  tests/test_tuple_transform_each

TESTS = $(check_PROGRAMS)

#List of source files needed to build the executable:

tests_test_tuple_cat_SOURCES = \
	tests/test_tuple_cat.cc
tests_test_tuple_cat_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_cat_LDADD = \
	$(PROJECT_LIBS)

tests_test_tuple_cdr_SOURCES = \
	tests/test_tuple_cdr.cc
tests_test_tuple_cdr_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_cdr_LDADD = \
	$(PROJECT_LIBS)

tests_test_tuple_end_SOURCES = \
	tests/test_tuple_end.cc
tests_test_tuple_end_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_end_LDADD = \
	$(PROJECT_LIBS)

tests_test_tuple_interlace_SOURCES = \
	tests/test_tuple_interlace.cc
tests_test_tuple_interlace_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_interlace_LDADD = \
	$(PROJECT_LIBS)

tests_test_tuple_start_SOURCES = \
	tests/test_tuple_start.cc
tests_test_tuple_start_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_start_LDADD = \
	$(PROJECT_LIBS)

tests_test_tuple_subset_SOURCES = \
	tests/test_tuple_subset.cc
tests_test_tuple_subset_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_subset_LDADD = \
	$(PROJECT_LIBS)

tests_test_tuple_transform_each_SOURCES = \
	tests/test_tuple_transform_each.cc
tests_test_tuple_transform_each_CXXFLAGS = \
	$(COMMON_CXXFLAGS)
tests_test_tuple_transform_each_LDADD = \
	$(PROJECT_LIBS)



