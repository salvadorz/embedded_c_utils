/*******************************************************************************
 * Copyright (C) 2023 by Salvador Z                                            *
 *                                                                             *
 * This file is part of C-UTILS                                                *
 *                                                                             *
 *   Permission is hereby granted, free of charge, to any person obtaining a   *
 *   copy of this software and associated documentation files (the Software)   *
 *   to deal in the Software without restriction including without limitation  *
 *   the rights to use, copy, modify, merge, publish, distribute, sublicense,  *
 *   and/or sell copies ot the Software, and to permit persons to whom the     *
 *   Software is furnished to do so, subject to the following conditions:      *
 *                                                                             *
 *   The above copyright notice and this permission notice shall be included   *
 *   in all copies or substantial portions of the Software.                    *
 *                                                                             *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   *
 *   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARANTIES OF MERCHANTABILITY *
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL   *
 *   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR      *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,     *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE        *
 *   OR OTHER DEALINGS IN THE SOFTWARE.                                        *
 ******************************************************************************/

/**
 * @file test_interpolate.c
 * @author Salvador Z
 * @date 22 Jun 2023
 * @brief File for test interpolate lib
 *
 */

#include "interpolate.h"
#include "uTest.h"

/*
Steering Problem

A controls engineer has collected test data for a black box steering system to
determine the amount of voltage that needs to be applied to hold the vehicle at a
given steering angle. The data below shows that the voltage (V)
required is a function of the steering angle (a).

Test Data:
a = -22,  -11, 0, 10,  20 degrees
V = -1.5, -1,  0, 1.2, 1.8 volts

The controls engineer would like to use this data as a feed forward term for the
steering controller. Your job is to write a function to determine
the best estimate for voltage (V) given a steering angle (a). aka. V = f(a).

Example output:
For a = 10; V = 1.2
For a = 5; V = 0.6
For a = 15; V = 1.5

This problem uses a unit test framework called Catch. Use the example tests at the
bottom of the file to test voltageEstimate, and feel free to add your own as well.
*/

void steering_test_interpolation(void) {

  const float a_data[] = { -22, -11, 0, 10, 20 };   // x-axis data
  const float v_data[] = { -1.5, -1, 0, 1.2, 1.8 }; // y-axis data
  const int   size     = 5;
  float       a, v_expected, v_test;

  // input angle
  a = 10.0;
  // expected output voltage
  v_expected = 1.2;
  // call function under test
  v_test = interpolated_estimate(a, a_data, v_data, size);

  // check that our result is correct (within floating point error)
  TEST_ASSERT_EQUAL_FLOAT_MSG(v_expected, v_test, "Angle in table (LUT)");

  // input angle
  a = 15.0;
  // expected output voltage
  v_expected = 1.5;
  // call function under test
  v_test = interpolated_estimate(a, a_data, v_data, size);

  // check that our result is correct (within floating point error)
  TEST_ASSERT_EQUAL_FLOAT_MSG(v_expected, v_test, "Interpolation between two values in LUT");

  // input angle
  a = 35.0;
  // expected output voltage
  v_expected = 1.8;
  // call function under test
  v_test = interpolated_estimate(a, a_data, v_data, size);

  // check that our result is correct (within floating point error)
  TEST_ASSERT_EQUAL_FLOAT_MSG(v_expected, v_test, "Angle outside of LUT (saturated high)");

  //  input angle
  a = -22.0;
  // expected output voltage
  v_expected = -1.5;
  // call function under test
  v_test = interpolated_estimate(a, a_data, v_data, size);

  // check that our result is correct (within floating point error)
  TEST_ASSERT_EQUAL_FLOAT_MSG(v_expected, v_test, "Angle within LUT (saturated low)");

  //  input angle
  a = 20.0;
  // expected output voltage
  v_expected = 1.8;
  // call function under test
  v_test = interpolated_estimate(a, a_data, v_data, size);

  // check that our result is correct (within floating point error)
  TEST_ASSERT_EQUAL_FLOAT_MSG(v_expected, v_test, "Angle within LUT (saturated high)");

  // input angle
  a = 5;
  // expected output voltage
  v_expected = 0.6;
  // call function under test
  v_test = interpolated_estimate(a, a_data, v_data, size);

  // check that our result is correct (within floating point error)
  TEST_ASSERT_EQUAL_FLOAT_MSG(v_expected, v_test, "Interpolation between two values in LUT");
}

void steering_test_interpolation_with_errors(void) {
  const float a_data[] = { -22, -11, 0, 10, 20 };   // x-axis data
  const float v_data[] = { -1.5, -1, 0, 1.2, 1.8 }; // y-axis data

  const float *a_data_err = NULL; // x-axis data
  const float *v_data_err = NULL; // y-axis data
  const int    size       = 3;
  float        a, v_expected, v_test;
  v_expected = 0.0f; // Expected error

  // input angle
  a = 10.0;
  // call function under test
  v_test = interpolated_estimate(a, a_data_err, v_data, size);

  // check that our result is correct (within floating point error)
  TEST_ASSERT_EQUAL_FLOAT_MSG(v_expected, v_test, "Angle data error");

  // input angle
  a = 15.0;
  // call function under test
  v_test = interpolated_estimate(a, a_data, v_data_err, size);

  // check that our result is correct (within floating point error)
  TEST_ASSERT_EQUAL_FLOAT_MSG(v_expected, v_test, "Volt data error");

  // input angle
  a = 35.0;
  // call function under test
  v_test = interpolated_estimate(a, a_data, v_data, 0u);

  // check that our result is correct (within floating point error)
  TEST_ASSERT_EQUAL_FLOAT_MSG(v_expected, v_test, "Testing with Size error");
}

int main(void) {
  uTEST_START();
  uTEST_ADD_MSG(steering_test_interpolation, "Steering Problem testing values within the table and saturated",
                64);
  uTEST_ADD_MSG(steering_test_interpolation_with_errors,
                "Steering Problem testing error handling", 129);

  return (uTEST_END());
}