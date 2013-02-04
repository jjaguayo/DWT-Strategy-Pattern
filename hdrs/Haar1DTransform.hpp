#ifndef _HAAR1DTRANSFORM_HPP
#define _HAAR1DTRANSFORM_HPP
#include "WaveletTransform.hpp"

class Haar1DTransform : public WaveletTransform
{
public:
  Haar1DTransform()
  {
  }

//
// Purpose:
//   Given a 1-D signal, compute discrete wavelet transform using 
//   the Haar wavelet up to a specific level.
//
// Input parameters:
//   inputData         - the data that will be transformed.
//   maxLevel          - the highest level of the coefficients.
//   lengthOfDimension - the length of each dimension of the input vector.
//                       Since this is a 1-D transform, it is expected that
//                       the vector have a single value.
//
// Return value:
//   An array representing the approximation and detail coefficients
//   up to a maximum level.
//
// Author:
//   Jose John Aguayo
//
// NOTE:
//   The method will throw an exception if 1) the input data size is not
//   a power of 2, 2) the max level requested is larger than
//   the max levels than can be achieved given the input data size
//   or 3) the number of dimensions in the third parameter is 
//   greater than 1.
//   The getMaxLevel method can be used to determine the 
//   maximum level that this method will accept.
//
  virtual double* analyze(double* inputData, int maxLevel, std::vector<int> lengthOfDimension);

//
// Purpose:
//   Given a set of coefficients, a starting level and the length of the 
//   input array, compute the input data that sourced the coefficients.
//
// Input parameters:
//   coefficients      - the coefficients that represent an original signal.
//                       It is expected that the approximation coefficients 
//                       are in the beginning of the array followed by the
//                       highest level detail coefficients and ending with
//                       lowest level (i.e. first level) detail coefficients.
//   maxLevel          - the highest level of the coefficients.
//   lengthOfDimension - the length of each dimension of the input vector.
//                       Since this is a 1-D transform, it is expected that
//                       the vector have a single value.
//
// Return value:
//   An array representing the input data that sourced the coefficients.
//
// Author:
//   Jose John Aguayo

// NOTES:
//   Still needs to be implemented
//
virtual  double* synthesize(double* coefficients, int maxLevel, std::vector<int> lengthOfDimension);

};

#endif
