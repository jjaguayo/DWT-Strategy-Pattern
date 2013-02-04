#include <iostream>
#include <iomanip>
#include <vector>
#include "haar1DTransform.hpp"

using namespace std;

//
// Purpose:
//   Test the WaveformTransform::getMaxLevels method
//
// Author:
//   Jose John Aguayo
//
void testGetMaxLevels()
{
  vector<int> lengthOfDimensions;
  vector<int> maxLevels;

  lengthOfDimensions.push_back(8); 
  int expectedDim = 3;

  maxLevels = Haar1DTransform::getMaxLevels(lengthOfDimensions);

  if (maxLevels[0] == expectedDim)
  {
    cout << "testGetMaxLevels passed" << endl;
  }
  else
  {
    cout << "testGetMaxLevels failed" << endl;
  }
}

//
// Purpose:
//   Test the Haar1DTransform::analyze method
//   Specifically, test that an exception is thrown if 
//   there is more than 1 dimension in length parameter
//
// Author:
//   Jose John Aguayo
//
void testHaar1DTransformAnalyze_1(WaveletTransform* dwt)
{
// setup
  bool exceptionThrown;
  //Haar1DTransform dwt;
  double* inputData = new double[8];
  vector<int> lengthOfDimensions;
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
  lengthOfDimensions.push_back(8);

// test
  try
  {
    coefficients = dwt->analyze(inputData,maxLevel,lengthOfDimensions);
  }
  catch (WaveletTransformException wte)
  {
    exceptionThrown = true;

  }

  if (exceptionThrown)
  {
    cout << "testHaar1DTransformAnalyze_1 passed" << endl;
  }
  else
  {
    cout << "testHaar1DTransformAnalyze_1 failed" << endl;
  }

// teardown
  delete [] inputData;
}

//
// Purpose:
//   Test the Haar1DTransform::analyze method
//   Specifically, test that an exception is thrown if 
//   the input data length is not a power of 2
//
// Author:
//   Jose John Aguayo
//
void testHaar1DTransformAnalyze_2(WaveletTransform* dwt)
{
// setup
  bool exceptionThrown;
  //Haar1DTransform dwt;

  // we know that with 9 elements, an exception
  // should be thrown
  double* inputData = new double[9];
  vector<int> lengthOfDimensions;
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
  inputData[8] = 5;

  lengthOfDimensions.push_back(9);

// test
  try
  {
    coefficients = dwt->analyze(inputData,maxLevel,lengthOfDimensions);
  }
  catch (WaveletTransformException wte)
  {
    exceptionThrown = true;

  }

  if (exceptionThrown)
  {
    cout << "testHaar1DTransformAnalyze_2 passed" << endl;
  }
  else
  {
    cout << "testHaar1DTransformAnalyze_2 failed" << endl;
  }
//teardown
  delete [] inputData;
}

//
// Purpose:
//   Test the Haar1DTransform::analyze method
//   Specifically, test that an exception is thrown if 
//   the max levels is more than allowed
//
// Author:
//   Jose John Aguayo
//
void testHaar1DTransformAnalyze_3(WaveletTransform* dwt)
{
// setup
  bool exceptionThrown;
  //Haar1DTransform dwt;
  double* inputData = new double[8];
  vector<int> lengthOfDimensions;
  double* coefficients;

  // we know that with 8 elements, the max level is 3.
  // with a level of 4, an exception should be thrown
  int maxLevel = 4;

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

// test
  try
  {
    coefficients = dwt->analyze(inputData,maxLevel,lengthOfDimensions);
  }
  catch (WaveletTransformException wte)
  {
    exceptionThrown = true;

  }

  if (exceptionThrown)
  {
    cout << "testHaar1DTransformAnalyze_3 passed" << endl;
  }
  else
  {
    cout << "testHaar1DTransformAnalyze_3 failed" << endl;
  }

  // teardown
  delete [] inputData;
}

// 
// Purpose:
//   Test the Haar1DTransform::analyze method with a specific set of input data,
//   and a specific set of expected results.
//
// Author:
//   Jose John Aguayo
//
bool testHaar1DTransformAnalyze_4_test(double* inputData, int maxLevel, vector<int> lengthOfDimensions, double* coefficients_level_data, WaveletTransform* dwt)
{
  //Haar1DTransform dwt;
  double* coefficients;

  bool testPassed;

  testPassed = true;

  try
  {
    coefficients = dwt->analyze(inputData,maxLevel,lengthOfDimensions);
  }
  catch (WaveletTransformException wte)
  {
  }

  for (int i=0;i<8 && testPassed;i++)
  {
    // we'll allow for some roundoff error up to .001
    if (0.001 < fabs(coefficients[i] - coefficients_level_data[i]))
    {
      testPassed = false;
    }
  }

  return testPassed;
}

//
// Purpose:
//   Test that the Haar1DTransform::analyze method computes the coefficients 
//   at specific levels correctly.
//   The input data and coefficients used for this test were taken
//   from "A Primer on WAVELETS and Their Scientific Applications"
//   by James S. Walker.
//   The coefficients can also easily be computed by hand using the
//   methods for finding fluctuations and trends described in the text.
//
// Author:
//   Jose John Aguayo
//
void testHaar1DTransformAnalyze_4(WaveletTransform* dwt)
{
// setup
  double* inputData = new double[8];
  double* coefficients_level1 = new double[8];
  double* coefficients_level2 = new double[8];
  double* coefficients_level3 = new double[8];
  vector<int> lengthOfDimensions;
  double* coefficients;
  int level;
  bool testPassed;
  int maxLevel;

  inputData[0] = 4;
  inputData[1] = 6;
  inputData[2] = 10;
  inputData[3] = 12;
  inputData[4] = 8;
  inputData[5] = 6;
  inputData[6] = 5;
  inputData[7] = 5;

  coefficients_level1[0] = 7.0711;
  coefficients_level1[1] = 15.556;
  coefficients_level1[2] = 9.8995;
  coefficients_level1[3] = 7.0711;
  coefficients_level1[4] = -1.4142;
  coefficients_level1[5] = -1.4142;
  coefficients_level1[6] = 1.4142;
  coefficients_level1[7] = 0;

  coefficients_level2[0] = 16;
  coefficients_level2[1] = 12;
  coefficients_level2[2] = -6;
  coefficients_level2[3] = 2;
  coefficients_level2[4] = -1.4142;
  coefficients_level2[5] = -1.4142;
  coefficients_level2[6] = 1.4142;
  coefficients_level2[7] = 0;

  coefficients_level3[0] = 19.799;
  coefficients_level3[1] = 2.8284;
  coefficients_level3[2] = -6;
  coefficients_level3[3] = 2;
  coefficients_level3[4] = -1.4142;
  coefficients_level3[5] = -1.4142;
  coefficients_level3[6] = 1.4142;
  coefficients_level3[7] = 0;

  lengthOfDimensions.push_back(8);

// test

  // test level 1 only

  maxLevel = 1;

  testPassed = testHaar1DTransformAnalyze_4_test(inputData, maxLevel, lengthOfDimensions, coefficients_level1,dwt);

  // test level 2 only
  if (testPassed)
  {
    maxLevel = 2;

    testPassed = testHaar1DTransformAnalyze_4_test(inputData, maxLevel, lengthOfDimensions, coefficients_level2,dwt);
  }

  // test level 3 only
  if (testPassed)
  {
    maxLevel = 3;

    testPassed = testHaar1DTransformAnalyze_4_test(inputData, maxLevel, lengthOfDimensions, coefficients_level3,dwt);
  }


  if (testPassed)
  {
    cout << "testHaar1DTransformAnalyze_4 passed" << endl;
  }
  else
  {
    cout << "testHaar1DTransformAnalyze_4 failed" << endl;
  }

  // teardown
  delete [] inputData;
  delete [] coefficients_level1;
  delete [] coefficients_level2;
  delete [] coefficients_level3;
}

// Purpose:
//   Calls all the functions that run specific test cases
//
// Author:
//   Jose John Aguayo
//
void testHaar1DTransformAnalyze(WaveletTransform* dwt)
{
  // Test cases
  //   1) more than 1 dimension in length parameter
  //   2) input data length is not a power of 2
  //   3) max levels is more than allowed
  //   4) for an input of size 8, calculate the coefficients for 
  //      max levels 0, 1, 2 and 3

  testHaar1DTransformAnalyze_1(dwt);
  testHaar1DTransformAnalyze_2(dwt);
  testHaar1DTransformAnalyze_3(dwt);
  testHaar1DTransformAnalyze_4(dwt);
}

// Purpose:
//   Test the Haar1DTransform::synthesize method.
//
// Author:
//   Jose John Aguayo
//
void testHaar1DTransformSynthesize(WaveletTransform* dwt)
{
// synthesize needs to be implemented and test cases need to be written
}

//
// Purpose:
//  The purpose of this program is to test the getMaxLevels method of the 
//  WaveletTransform class and the analyze and synthesis methods of its
//  subclasses
//
// Author:
//   Jose John Aguayo

// NOTE:
//   The only concrete subclass currently implemented is the Haar1DTransform
//   subclass and of that the synthesize method still needs to be implemented.
//   The test cases will be implemented for that method when the method is 
//   written.
//   Also note that the test cases are not exhaustive and most likely a better
//   framework for setting up, executing and tearing down test cases needs
//   to be utilized (e.g. cppunit). Given time, this will be done.
int
main(int argc, char **argv)
{
  WaveletTransform* dwt = new Haar1DTransform();
  testHaar1DTransformAnalyze(dwt);
  testHaar1DTransformSynthesize(dwt);
  testGetMaxLevels();

  delete dwt;
}
