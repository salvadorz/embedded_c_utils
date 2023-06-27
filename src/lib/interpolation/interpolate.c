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
 * @file interpolate.c
 * @author Salvador Z
 * @date 06 Jun 2023
 * @brief File for Estimate a linear Interpolation from a given datasets (domain and range values)
 *
 */

#include "interpolate.h"

float32_t interpolated_constant(float32_t const m, float32_t const x0, float32_t const y0) {
  float32_t const return_k = y0 - (m * x0);
  return return_k;
}

float32_t interpolated_estimate(float32_t const input, float32_t const *domain, float32_t const *range,
                                int32_t length) {
  float32_t f32_range_est = 0.0f;

  if ((NULL == domain) || (NULL == range) || (1 > length)) {
    // ASSERT(domain && range && (1 < length));
    return 0.0f; // exit(1)?
  } else {
    if (input <= domain[0U]) // Saturate case
      f32_range_est = range[0U];

    else if (input >= domain[length - 1]) // Saturate case
      f32_range_est = range[length - 1];

    else {
      /* Range from 1 to len-1 (Only len-1 iter) The range[len-1] is validated on
       * previous `else if` (saturate) case */
      for (int32_t i = 1; i < length; ++i) {

        if (input == domain[i - 1]) {
          f32_range_est = range[i - 1];
          break; // No need to check anymore
        }

        else if ((input > domain[i - 1]) && (input < domain[i])) {
          float const delta_y = range[i] - range[i - 1];
          float const delta_x = domain[i] - domain[i - 1]; // Can't be 0
          float const m       = delta_y / delta_x;
          float const k       = interpolated_constant(m, domain[i - 1], range[i - 1]);

          f32_range_est = ((m * input) + k);
          break;
        }
      }
    }
  }

  return f32_range_est;
}