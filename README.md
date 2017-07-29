DWT-Strategy-Pattern
====================
This project contains a simple object oriented implementation of the Haar wavelet
transform. The project aims to make use of a simple Strategy pattern where an
abstract class, WaveletTransform, defines two virtual methods, analyze and
synthesize and expects subclasses to implement the algorithms based on
factors such as the type of mother wavelet used or the type of architecture
that the code is running on.

Initially, a Haar wavelet utilized on a 1D signal will be implemented but over time,
the code can be extended to work with other wavelets (e.g. Daubechies),
other signal types (e.g. 2-D signals) and other architectures (e.g. parallel
or distributed systems).

Template signatures were considered as an implementation of the Strategy
pattern but in the end, using concrete subclasses seemed more flexible for the
user as the template type would need to be specified at compile time, however,
the subclass approach allowed concrete algorithms to be instantiated at run time.

Some current todos in the short term given how I hope to do

1) Add a Jenkinsfile to automate build and test
2) Modify the CMakeList files to build on Mac and Windows
3) implement the analyze / synthesize methods for a few more "complex" wavelets

Dependencies
============
CMake 3.0 or higher
A C++11 compiler
Linux

Build
=====
This project endorses out-of-source building, so to build the project, cd to the base directory and execute the following:

```
mkdir build
cd build
make
```

The Wavelet transform functions will be located in a shared library in the lib/ directory.

Testing
=======
After building, the suite of tests can be run from the build directory with the following command:
```
make test ARGS="-V"
```

or 

```
ctest -V
```
