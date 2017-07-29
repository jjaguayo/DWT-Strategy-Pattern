#include "Haar1DTransform.hpp"

#include "gtest/gtest.h"
#include <vector>
#include <cmath>

TEST(Haar1DTransform,valid_inputs) {
  const int inputLength = 8;
  WaveletTransform* dwt = new Haar1DTransform();
  double inputData[inputLength] = { 4, 6, 10, 12, 8, 6, 5, 5 };
  std::vector<int> lengthOfDimensions;

  lengthOfDimensions.push_back(inputLength);

  std::vector<int> allowedMaxLevels = WaveletTransform::getMaxLevels(lengthOfDimensions);

  double* transformData = dwt->analyze(inputData, allowedMaxLevels.at(0), lengthOfDimensions);
  double* inverseTransformData = dwt->synthesize(transformData, allowedMaxLevels.at(0), lengthOfDimensions);

  for (int i = 0; i < lengthOfDimensions.at(0); i++) {
    ASSERT_PRED_FORMAT2(::testing::DoubleLE, std::abs(inverseTransformData[i] - inputData[i]), 1e-9);
  }

  delete [] transformData;
  delete [] inverseTransformData;
}
