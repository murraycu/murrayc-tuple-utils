# murrayc-tuple-utils
A rough collection of code to manipulate C++ std::tuple&lt;>s.

[![Build Status](https://travis-ci.org/murraycu/murrayc-tuple-utils.svg?branch=master)](https://travis-ci.org/murraycu/murrayc-tuple-utils)

## Basic Usage

Include the specific header. For instance,
```C++
#include <tuple-utils/tuple_end.h>
```

If your source file is program.cc, you can compile it with:
```shell
g++ program.cc -o program `pkg-config --cflags --libs murrayc-tuple-utils-1.0`
```

## Using Autotools

Alternatively, if using autoconf, use the following in configure.ac:
```m4
PKG_CHECK_MODULES([DEPS], [murrayc-tuple-utils-1.0])
```

Then use the generated DEPS_CFLAGS and DEPS_LIBS variables in the project Makefile.am files. For example:
```Makefile
yourprogram_CPPFLAGS = $(DEPS_CFLAGS)
yourprogram_LDADD = $(DEPS_LIBS)
```

Your PKG_CHECK_MODULES() call should also mention any other libraries that you need to use via pkg-config.

## Using CMake

If using CMake, use the following in CMakeList.txt:
```CMake
include(FindPkgConfig)
pkg_check_modules(DEPS REQUIRED murrayc-tuple-utils-1.0)
include_directories(${DEPS_INCLUDE_DIRS})
target_link_libraries(yourprogram ${DEPS_LIBRARIES})
```

Your pkg_check_modules() call should also mention any other libraries that you need to use via pkg-config
