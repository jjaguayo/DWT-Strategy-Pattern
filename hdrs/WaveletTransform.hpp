#ifndef _WAVELET_TRANSFORM_HPP
#define _WAVELET_TRANSFORM_HPP

#include <vector>
#include <string>
#include <math.h>

// WaveletTransform is an abstract class which functions as an interface 
// for subclasses that can be used to analyze or synthesize data using 
// the discrete wavelet transform and various other mother wavelets.
// One method will be implemented , getMaxLevels. All other 
// method should be implemented by concrete subclasses.

class WaveletTransform
{
public:
  virtual double* analyze(double* inputData, int maxLevel, std::vector<int> lengthOfDimension) = 0;

  virtual double* synthesize(double* inputData, int maxLevel, std::vector<int> lengthOfDimension) = 0;

  //
  // Purpose:
  //   For each dimension of the input data, getMaxLevels returns the 
  //   maximum decomposition level that can be acheived given the length 
  //   of a dimension of the input. The maximum decomposition level is 
  //   the floor of the log base 2 of the dimension length.
  //
  // Input parameters:
  //
  //   lengthOfDimension - the length of each dimension of a set of input 
  //                       data. For 1-D data, there would be 1 element; 
  //                       for 2-D, two elements.
  //
  // Return value:
  //
  //   A vector of the maximum levels for each dimension
  //
  // Author:
  //   Jose John Aguayo
  //
  // NOTES:
  // 
  static std::vector<int> getMaxLevels(std::vector<int> lengthOfDimension)
  {
    std::vector<int> maxLevels;
    int dimensionSize;
    int aMaxValue;

    // for each dimension, find the smallest power of 2 and push that 
    // value onto the vector

    for (int i=0; i < lengthOfDimension.size();i++)
    {
      dimensionSize = lengthOfDimension[i];
      aMaxValue = floor(log2(dimensionSize));
      maxLevels.push_back(aMaxValue);
    }

    return maxLevels;
  }

protected:
  WaveletTransform()
  {
  }
};


class WaveletTransformException
{
public:
  WaveletTransformException(std::string msg):message(msg)
  {
  }

  std::string what()
  {
    return message;
  }
protected:
  std::string message;
};
#endif
