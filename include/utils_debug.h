/*******************************************************************************
 * Copyright (C) 2023 by Salvador Z                                            *
 *                                                                             *
 * This file is part of UTILS_C                                                *
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
 * @file utils_debug.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Common and variable/base datatypes and constant macros for debugging purposes
 *
 */

#ifndef UTILS_DEBUG_H_
#define UTILS_DEBUG_H_

// Includes

#define DEBUG (1U)

#define SEND_OUT() fflush(stdout)

#define SEND_ALL() \
  fflush(stdin);   \
  fflush(stdout)
#define FLUSH_AFTER_PRINTF()     \
  setvbuf(stdout, 0, _IONBF, 0); \
  setvbuf(stdin, 0, _IONBF, 0)

#if DEBUG
  // https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
  // __VA_OPT__(,) __VA_ARGS__)
  #define DEBUG_LOG(msg, ...)                  \
    printf("DEBUG: " msg "\n", ##__VA_ARGS__); \
    SEND_OUT()
  #define ERROR_LOG(msg, ...)                    \
    printf("ERROR:\n " msg "\n", ##__VA_ARGS__); \
    SEND_OUT()
#else
  #define DEBUG_LOG(msg, ...)
  #define ERROR_LOG(msg, ...)
#endif

#ifndef PASS
  #define PASS (0U)
#endif

#ifndef DISABLE
  #define DISABLE (0U)
#endif

#ifndef ENABLE
  #define ENABLE (1U)
#endif

#if !defined(PASSED) && !defined(FAILED)
  #define PASSED(x)            (PASS == (x))
  #define FAILED(x)            (PASS != (x))
  #define EXPECTED_VAL(tst, x) ((tst) == (x))
#endif
// clang-format off
#define PASSED_MARK (u8"\u2713")
#define FAILED_MARK (u8"\u2717")
// clang-format on
#endif /* UTILS_DEBUG_H_ */