/**
 * @file utils_common.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Common and variable/base datatypes and constant macros
 *
 */

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

#ifndef UTILS_COMMON_H_
#define UTILS_COMMON_H_

// Includes
#include <stdbool.h>

// clang-format off
typedef volatile unsigned char      vuint8_t;   /*unsigned  8 bit definition */
typedef volatile unsigned short     vuint16_t;  /*unsigned 16 bit definition */
typedef volatile unsigned int       vuint32_t;  /*unsigned 32 bit definition */
typedef volatile unsigned long long vuint64_t;  /*unsigned 64 bit definition */

typedef volatile signed char        vint8_t;   /*signed  8 bit definition */
typedef volatile signed short       vint16_t;  /*signed 16 bit definition */
typedef volatile signed int         vint32_t;  /*signed 32 bit definition */
typedef volatile signed long long   vint64_t;  /*signed 64 bit definition */

typedef unsigned char               uint8_t;   /*unsigned  8 bit definition */
typedef unsigned short              uint16_t;  /*unsigned 16 bit definition */
typedef unsigned int                uint32_t;  /*unsigned 32 bit definition */
typedef unsigned long int           uint64_t;  /*unsigned 64 bit definition */

typedef signed char                 int8_t;    /*signed  8 bit definition */
typedef signed short                int16_t;   /*signed 16 bit definition */
typedef signed int                  int32_t;   /*signed 32 bit definition */
typedef signed long int             int64_t;   /*signed 64 bit definition */
// clang-format on
typedef float       float32_t;
typedef double      float64_t;
typedef long double float128_t;

typedef bool    bool_t;
typedef uint8_t base_t;

/*****************************************************************************************************
 * Definition of module wide MACROs / #DEFINE-CONSTANTs
 *****************************************************************************************************/

/* Common Constants */
#ifndef ON
  #define ON (1U)
#endif

#ifndef OFF
  #define OFF (0U)
#endif

#ifndef OK
  #define OK (0U)
#endif

#ifndef NOT_OK
  #define NOT_OK (1U)
#endif

#ifndef BUSY_W
  #define BUSY_W (2U)
#endif

#ifndef ERROR
  #define ERROR (0xFFU) /* UINT8_MAX - Error for base_t type*/
#endif

#ifndef TRUE
  #define TRUE (1U)
#endif

#ifndef FALSE
  #define FALSE (0U)
#endif

#ifndef PASS
  #define PASS (0U)
#endif

#ifndef FAIL
  #define FAIL (1U)
#endif

#ifndef SET
  #define SET (1U)
#endif

#ifndef CLEAR
  #define CLEAR (0U)
#endif

#ifndef DISABLE
  #define DISABLE (0U)
#endif

#ifndef ENABLE
  #define ENABLE (1U)
#endif

#ifndef NULL
  #define NULL ((void *)0)
#endif

#ifndef _UNUSED
  #define _UNUSED(x) ((void)(x))
#endif

#ifndef DEREFERENCE_TO
  #define DEREFERENCE_TO(type) (*(type *))
#endif

#ifndef ASSERT
  #define ASSERT(expr) assert(expr)
#endif
#endif /* UTILS_COMMON_H_ */