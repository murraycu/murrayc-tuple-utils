# Building murrayc-tuple-utils

On Linux, you would ideally get murrayc-tuple-utils from your distro's official package.
However, this is about building from source.

## autotools

murrayc-tuple-utils uses autotools as its main build system,

### Building from a tarball

You can build or install with the regular configure/make steps.
For instance:
  ./configure --prefix=/opt/something
then
  make
or
  make install
You can build the examples and tests, and run the tests, like so:
  make check
We create the tarball release like so:
  make distcheck


### Building from git

You will need to get both the git module and its git submodules, like so:

  $ git clone git@github.com:murraycu/murrayc-tuple-utils.git
  $ cd murrayc-tuple-utils
  $ git submodule update --init --recursive

The autogen.sh script generates the build files and calls ./configure.

For instance:
  ./autogen.sh --prefix=/opt/something --enable-warnings=fatal
then
  make
or
  make install
You can build the examples and tests, and run the tests, like so:
  make check
We create the tarball release like so:
  make distcheck

## CMake

You may also build murrayc-tuple-utils with CMake, though it's fairly experimental for now.
For instance,
  cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/something .
then
  make
or
  make install
You can run the tests like so:
  make test

