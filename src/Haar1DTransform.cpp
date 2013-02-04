#include "Haar1DTransform.hpp"

using namespace std;

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
//   Need to recognize John Burkardt as his algorithm along with
//   the text "A Primer on WAVELETS and Their Scientific Applications"
//   by James S. Walker have been instrumental in getting started with this 
//   code.
//
double* Haar1DTransform::analyze(double* inputData, int maxLevel, vector<int> lengthOfDimension)
{
  double* finalCoefficients;
  double* singleLevelCoefficients;
  unsigned int totalLength;
  int currentLevel;
  unsigned int currentLvlCoeffSetSize;
  vector<int> allowedMaxLevels = WaveletTransform::getMaxLevels(lengthOfDimension);

  // Haar coefficients used in this algorithm.
  double H0 = 0.7071067811865475;
  double H1 = 0.7071067811865475;

  // this is a transform for 1D data; throw an exception if the data is 
  // not 1 dimensional
  if (lengthOfDimension.size() > 1)
  {
    throw WaveletTransformException(string("Only 1 dimension allowed"));
  }

  // for now, we can only have input lengths that are a power of 2
  totalLength = lengthOfDimension[0];
  if ((totalLength & (totalLength - 1)) != 0)
  {
    throw WaveletTransformException("input length must equal a power of 2");
  }

  // if the levels being asked for are more than can be computed, throw an 
  // exception
  if (maxLevel > allowedMaxLevels[0])
  {
    string msg;
    int allowedLevels = allowedMaxLevels[0];
    msg += "Only ";
    msg += + allowedLevels;
    msg += " levels allowed";
    throw WaveletTransformException(msg);
  }

  // allocate space for the coefficients variable 
  finalCoefficients = new double[totalLength];
  singleLevelCoefficients = new double[totalLength];

  for (int i=0;i< totalLength;i++)
  {
    finalCoefficients[i] = inputData[i];
    singleLevelCoefficients[i] = 0.0;
  }

  // calculate coefficients at each level until we reach the max level wanted
  currentLevel = 0;
  currentLvlCoeffSetSize = totalLength;

  while (currentLevel < maxLevel)
  {
    currentLvlCoeffSetSize = currentLvlCoeffSetSize >> 1;

    // Calculate the approximation and detail coefficients for a given level
    for (int i = 0; i < currentLvlCoeffSetSize ;i++)
    {
      singleLevelCoefficients[i] = H0 * (finalCoefficients[2*i] + finalCoefficients[2*i+1]);
      singleLevelCoefficients[i + currentLvlCoeffSetSize ] = 
        H1 * (finalCoefficients[2*i] - finalCoefficients[2*i+1]);
    }

    // write the single level coefficients back to the final coefficients
    for (int i = 0; i < 2 * currentLvlCoeffSetSize ; i++)
    {
      finalCoefficients[i] = singleLevelCoefficients[i];
    }
    
    currentLevel++;
  }

  delete [] singleLevelCoefficients;

  return finalCoefficients;
}

//
// Purpose:
//   Given a set of coefficients, a starting level and the length of the input
//   array, compute the input data that sourced the coefficients.
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
// Return value:
//   An array representing the input data that sourced the coefficients.

// Author:
//   Jose John Aguayo

// NOTES:
//   Still needs to be implemented
//
double* Haar1DTransform::synthesize(double* coefficients, int maxLevel, vector<int> lengthOfDimension)
{
  double* outputData;

  return outputData;
}
