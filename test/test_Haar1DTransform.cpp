#include "Haar1DTransform.hpp"

#include "gtest/gtest.h"
#include <vector>

TEST(Haar1DTransform,constructor) {
  WaveletTransform* dwt = new Haar1DTransform();
  bool exceptionThrown;
  double* inputData = new double[8];
  std::vector<int> lengthOfDimensions;
  double* coefficients;
  int maxLevel = 2;

  exceptionThrown = false;

  inputData[0] = 4;
  inputData[1] = 6;
  inputData[2] = 10;
  inputData[3] = 12;
  inputData[4] = 8;
  inputData[5] = 6;
  inputData[6] = 5;
  inputData[7] = 5;

  lengthOfDimensions.push_back(8);
  delete [] inputData;
}
