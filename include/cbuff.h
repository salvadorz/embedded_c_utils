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
 * @file cbuff.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Circular/ring buffer public apis
 *
 */

#ifndef CBUFF_H_
#define CBUFF_H_

// Includes
#include "cbuff/cbuff_datatypes.h"

typedef cbuff_t *cbuff_handle_t;

/**
 * \brief    Initializes the circular buffer
 * \param    cb - circular buffer handle to assing the
 * \param    buffer reference and its maximum
 * \param    length or capacity of the buffer and size of every
 * \param    element_sz of the buffer
 * \return   OK if success, NOT_OK otherwise
 * \todo
 */
base_t cbuff_init(cbuff_handle_t cb, void *const buffer, uint16_t const length, uint8_t const element_sz);

/**
 * \brief    Circular buffer reset function by putting in a known state
 * \param    cb - circular buffer to put in a known state by resetting all its members
 * \return   OK if success, NOT_OK otherwise
 * \todo
 */
base_t cbuff_reset(cbuff_handle_t cb);

/**
 * \brief    Insert new data to the circular buffer
 * \param    cb - circular buffer handle to add the
 * \param    element on its head buffer
 * \return   OK if success, NOT_OK otherwise
 * \todo
 */
base_t cbuff_push(cbuff_handle_t cb, void *const element);

/**
 * \brief    Retrieves the oldest data from the circular buffer
 * \param    cb - circular buffer handle to retrieve the
 * \param    element from its buffer tail (oldest data)
 * \return   OK if success, NOT_OK otherwise
 * \todo
 */
base_t cbuff_pop(cbuff_handle_t cb, void *element);

/**
 * \brief    Provides the current buffer number of elements
 * \param    cb - circular buffer to get it's current
 * \return   size (elements), 0 if empty or NULL provided
 * \todo
 */
uint16_t cbuff_size(cbuff_handle_t cb);

#endif /* CBUFF_H_ */