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

Some current todos in the short term given how I hope to utilize these
classes are

1) implement the synthesize method for the Haar 1D transform.
2) implement the analyze methods for a few more "complex" wavelets

Some longer term todos include
1) integrate a better testing framework
2) construct a more thorough set of test cases
