include $(top_srcdir)/tuple-utils/filelist.am

book_name = $(MURRAYC_TUPLE_UTILS_MODULE_NAME)
doc_input = $(addprefix $(top_srcdir)/,$(h_sources_public))

# Sets dist_noinst_DATA, DISTCLEANFILES and MAINTAINERCLEANFILES
include $(top_srcdir)/build/doc-reference.am

# These are copied here by mm-common:
dist_noinst_DATA += \
	doc-install.pl \
	doc-postprocess.pl \
	tagfile-to-devhelp2.xsl \
	doxygen.css

