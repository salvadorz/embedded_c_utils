/*******************************************************************************
 * Copyright (C) 2023 by Salvador Z                                            *
 *                                                                             *
 * This file is part of C_UTILS                                                *
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
 * @file interpolate.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Estimate a linear Interpolation
 *
 */

#ifndef INTERPOLATE_H_
#define INTERPOLATE_H_

// Includes
#include "utils_common.h"

/**
 * @brief Calculates the interpolated constant value based on given data points.
 *
 * This function calculates the interpolated constant value using the linear interpolation method.
 * It takes the slope (m), initial x-value (x0), and initial y-value (y0) as input parameters.
 *
 * @param m The slope of the linear interpolation.
 * @param x0 The initial x-value.
 * @param y0 The initial y-value.
 * @return The interpolated constant value.
 */
float32_t interpolated_constant(float32_t const m, float32_t const x0, float32_t const y0);

/**
 * @brief Estimates the output value based on the input and given data points.
 *
 * This function estimates the output value (Y) for a given input (X) using the linear interpolation method.
 * It takes the input value, two arrays representing the domain (sampled input data) and range (sampled output
 * data), and the length of the arrays as input parameters. If the given value matches a value from the
 * domain, then will return the range value from the given data set (as a simple LUT). If the input value does
 * not match then will find it's position on the domain data set (domain[x-1] < input <domain[x]) and estimate
 * its range value. If the input is out-of-range from the given domain data set then will provide a saturated
 * behavior.
 *
 * @param input The input value for which the output needs to be estimated.
 * @param domain The array containing the sampled input data (x-axis).
 * @param range The array containing the sampled output data (y-axis).
 * @param length The length of the input and output arrays.
 * @return The estimated output value.
 */
float32_t interpolated_estimate(float32_t const input, float32_t const *domain, float32_t const *range,
                                int32_t length);

#endif /* INTERPOLATE_H_ */