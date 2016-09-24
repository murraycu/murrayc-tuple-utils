# Copyright 2016, The murrayc-tuple-utils Development Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

set (SOURCE_FILES
  tuple_cat.h
  tuple_end.h
  tuple_interlace.h
  tuple_start.h
  tuple_transform_each.h
  tuple_cdr.h
  tuple_for_each.h
  tuple_print.h
  tuple_subset.h
)

# We don't need to build a library, because this is a headers-only library:
set (MURRAYC_TUPLE_UTILS_LIB_NAME murrayc-tuple-utils-${MURRAYC_TUPLE_UTILS_API_VERSION})
#
# add_library(${MURRAYC_TUPLE_UTILS_LIB_NAME} SHARED ${SOURCE_FILES})
#
# set_property (TARGET ${MURRAYC_TUPLE_UTILS_LIB_NAME} PROPERTY VERSION ${PACKAGE_VERSION})
# set_property(TARGET ${MURRAYC_TUPLE_UTILS_LIB_NAME}  PROPERTY SOVERSION ${LIBMURRAYC_TUPLE_UTILS_SOVERSION})

set (INCLUDE_INSTALL_DIR "include/${PROJECT_NAME}-${MURRAYC_TUPLE_UTILS_API_VERSION}")

install (
	DIRECTORY "${PROJECT_SOURCE_DIR}"
	DESTINATION "${INCLUDE_INSTALL_DIR}"
	FILES_MATCHING PATTERN "*.h"
)

