#include "Haar1DTransform.hpp"

#include <cstdlib>

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
double* Haar1DTransform::analyze(double* inputData, int maxLevel, std::vector<int> lengthOfDimension)
{
    double* finalCoefficients;
    double* singleLevelCoefficients;
    unsigned int totalLength;
    int currentLevel;
    unsigned int currentLvlCoeffSetSize;
    std::vector<int> allowedMaxLevels = WaveletTransform::getMaxLevels(lengthOfDimension);
  
    // Haar coefficients used in this algorithm.
    double H0 = 0.7071067811865475;
    double H1 = 0.7071067811865475;
  
    // this is a transform for 1D data only
    if (lengthOfDimension.size() != 1) {
        throw WaveletTransformException(std::string("Only 1 dimension allowed"));
    }
  
    // for now, we can only have input lengths that are a power of 2
    totalLength = lengthOfDimension[0];
    if ((totalLength & (totalLength - 1)) != 0) {
        throw WaveletTransformException("input length must equal a power of 2");
    }
  
    // max levels requested must be less than max allowed
    if (maxLevel > allowedMaxLevels[0]) {
        std::string msg = "Only";
        msg += allowedMaxLevels[0] + " levels allowed";
        throw WaveletTransformException(msg);
    }
  
    finalCoefficients = new double[totalLength];
    singleLevelCoefficients = new double[totalLength];
  
    for (int i=0;i< totalLength;i++) {
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
        for (int i = 0; i < currentLvlCoeffSetSize ;i++) {
            singleLevelCoefficients[i] = 
                H0 * (finalCoefficients[2*i] + finalCoefficients[2*i+1]);

            singleLevelCoefficients[i + currentLvlCoeffSetSize] = 
                H1 * (finalCoefficients[2*i] - finalCoefficients[2*i+1]);
        }
  
        // write the single level coefficients back to the final coefficients
        for (int i = 0; i < 2 * currentLvlCoeffSetSize ; i++) {
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
double* Haar1DTransform::synthesize(double* coefficients, int maxLevel, std::vector<int> lengthOfDimension)
{
    double* outputData;
    double* intermediateResults;
    int totalLength;
    int currentLevel;
    std::vector<int> allowedMaxLevels = WaveletTransform::getMaxLevels(lengthOfDimension);
  
    // this is a transform for 1D data only
    if (lengthOfDimension.size() != 1) {
        throw WaveletTransformException(std::string("Only 1 dimension allowed"));
    }
  
    // for now, we can only have input lengths that are a power of 2
    totalLength = lengthOfDimension[0];
    if ((totalLength & (totalLength - 1)) != 0) {
        throw WaveletTransformException("input length must equal a power of 2");
    }
  
    // max levels requested must be less than max allowed
    if (maxLevel > allowedMaxLevels[0]) {
        std::string msg = "Only";
        msg += allowedMaxLevels[0] + " levels allowed";
        throw WaveletTransformException(msg);
    }
  
    double H = 0.7071067811865475;
  
    outputData = new double[totalLength];
    intermediateResults = new double[totalLength];
  
    for (auto i = 0; i < totalLength; i++) {
        outputData[i] = coefficients[i];
        intermediateResults[i] = 0.0;
    }
  
    currentLevel = 1;

    while((currentLevel << 1) <= totalLength) {
        for (auto i = 0; i < currentLevel; i++) {
            intermediateResults[2*i] = H * (outputData[i] + outputData[i+currentLevel]);
            intermediateResults[(2*i) + 1] = H * (outputData[i] - outputData[i+currentLevel]);
        }
  
        for (auto i = 0; i < (currentLevel << 1); i++) {
            outputData[i] = intermediateResults[i];
        }
  
        currentLevel <<= 1;
    }
  
    delete [] intermediateResults;
  
    return outputData;
}
