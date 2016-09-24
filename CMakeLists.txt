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

cmake_minimum_required (VERSION 3.2)

set (MURRAYC_TUPLE_UTILS_MAJOR_VERSION 0)
set (MURRAYC_TUPLE_UTILS_MINOR_VERSION 0)
set (MURRAYC_TUPLE_UTILS_MICRO_VERSION 3)

set (MURRAYC_TUPLE_UTILS_API_VERSION 1.0)
set (PACKAGE_VERSION ${MURRAYC_TUPLE_UTILS_MAJOR_VERSION}.${MURRAYC_TUPLE_UTILS_MINOR_VERSION}.${MURRAYC_TUPLE_UTILS_MICRO_VERSION})
set (MURRAYC_TUPLE_UTILS_SOVERSION 0)

project (murrayc_tuple_utils)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set (PROJECT_SOURCE_DIR "${murrayc_tuple_utils_SOURCE_DIR}/murrayc-tuple-utils")

include_directories (${murrayc_tuple_utils_SOURCE_DIR})
include_directories (${murrayc_tuple_utils_BINARY_DIR})

set (prefix ${CMAKE_INSTALL_PREFIX})
set (exec_prefix \${prefix})
set (libdir \${exec_prefix}/lib)
set (datarootdir \${prefix})
set (datadir \${datarootdir})
set (includedir \${prefix}/include)
set (top_srcdir .)
configure_file (murrayc-tuple-utils.pc.in murrayc-tuple-utils-${MURRAYC_TUPLE_UTILS_API_VERSION}.pc @ONLY)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
 	IMMEDIATE @ONLY)

add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)


install (FILES
			"${CMAKE_CURRENT_BINARY_DIR}/murrayc-tuple-utils-${MURRAYC_TUPLE_UTILS_API_VERSION}.pc"
		DESTINATION
			"${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")

enable_testing()



add_subdirectory (googletest)
add_subdirectory (tuple-utils)
add_subdirectory (tests)


set (PROJECT_CMAKE_NAME		"${PROJECT_NAME}-1")
set (VERSION_CONFIG     	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_CMAKE_NAME}ConfigVersion.cmake")
set (LIBMURRAYC_TUPLE_UTILS_INCLUDE_DIR	"${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME}-${MURRAYC_TUPLE_UTILS_API_VERSION}/include")
set (PROJECT_CONFIG     	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_CMAKE_NAME}Config.cmake")
set (CONFIG_INSTALL_DIR 	"lib/cmake/${PROJECT_CMAKE_NAME}")
set (TARGETS_EXPORT_NAME    "${PROJECT_CMAKE_NAME}Targets")
include (CMakePackageConfigHelpers)

write_basic_package_version_file (
    "${VERSION_CONFIG}"
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file (
    "cmake/murrayc-tuple-utils-1Config.cmake.in"
    "${PROJECT_CONFIG}"
    INSTALL_DESTINATION "${CONFIG_INSTALL_DIR}"
)

install (
    FILES "${PROJECT_CONFIG}" "${VERSION_CONFIG}"
    DESTINATION "${CONFIG_INSTALL_DIR}"
)

