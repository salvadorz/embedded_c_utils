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
#include "cbuff/cbuff_defines.h"

/**
 * Description:
 *   Defines a global circular buffer `buff` of a given type and length (size).
 *    The type can be native data types or user-defined data types.
 *
 * Usage:
 *   CBUFF_CREATE(uint8_t, byte_buf, 15);
 *   CBUFF_CREATE(struct foo, foo_buf, 10);
 */
#define CBUFF_CREATE(type, buff, length) _CBUFF_DEF_TYPE(type, buff, length)

/**
 * Description:
 *   Resets the Circular buffer, putting it in a known (default) state.
 *   Note: Does not clean the freed slots.
 */
#define CBUFF_FLUSH(buff) \
  do {                    \
    buff.u16_head = 0;    \
    buff.u16_tail = 0;    \
  } while (0)

/**
 * Description:
 *   Inserts the element pointed to by `elem` at the head of the circular buffer `buff`.
 *   After the write, the occupancy count increases by one.
 *
 * Returns (base_t):
 *   0 - Success
 *   1 - Out of space
 */
#define CBUFF_PUT(buff, elem) buff##_push_refd(elem)

/**
 * Description:
 *   Inserts (forced) the element pointed to by `elem` at the head of the circular buffer `buff`.
 *   If the buffer is full the oldest data is overwritten and the count is not increased otherwise increases.
 *
 * Returns (base_t):
 *   0 - Success
 *   1 - Out of space
 */
#define CBUFF_PUSH(buff, elem) buff##_push_ovwr(elem)

/**
 * Description:
 *   Copies the element at the tail of the circular buffer `buff` into the location pointed
 *   to by `elem`. This method is read-only and does not affects the occupancy status.
 *
 * Returns (base_t):
 *   0 - Success
 *   1 - Empty
 */
#define CBUFF_GET(buff, elem) buff##_get_refd(elem)

/**
 * Description:
 *   Removes the element at the tail of the circular buffer `buff` and makes it
 *   available at `elem`. This is a read-write method, and the occupancy count reduces
 *   by one.
 *
 * Returns (base_t):
 *   0 - Success
 *   1 - Empty
 */
#define CBUFF_POP(buff, elem) buff##_pop_refd(elem)

/**
 * Description:
 *   Returns the number of free slots in the circular buffer `buff`.
 *
 * Returns (int):
 *   0..N - Number of slots available.
 */
#define CBUFF_SPACES(buff) (buff.u16_lgth - cbuff_size(&buff))

typedef cbuff_t *cbuff_handle_t;

/**
 * \brief    Initializes the circular buffer
 * \param    cb - circular buffer handle to assign the
 * \param    buffer reference and its maximum
 * \param    length or capacity of the buffer (maximum number of elements) and size of each
 * \param    element_sz in the buffer
 * \return   OK if successful, NOT_OK otherwise.
 * \todo
 */
base_t cbuff_init(cbuff_handle_t cb, void *const buffer, uint16_t const length, uint8_t const element_sz);

/**
 * \brief    Resets the Circular buffer, putting it in a known state
 * \param    cb - circular buffer to be reset by resetting all its members
 * \return   OK if successful, NOT_OK otherwise.
 * \todo
 */
base_t cbuff_reset(cbuff_handle_t cb);

/**
 * \brief    Inserts new data into the circular buffer
 * \param    cb - circular buffer handle to add the
 * \param    element to its head buffer if
 * \param    forced then it will overwrite the oldest data
 * \return   OK if successful, NOT_OK otherwise
 * \todo
 */
base_t cbuff_push(cbuff_handle_t cb, void *const element, bool_t const forced);

/**
 * \brief    Retrieves the oldest data from the circular buffer
 * \param    cb - circular buffer handle to retrieve the
 * \param    element from its tail buffer (oldest data), if
 * \param    rd_only a read will be performed but the data will be retained in the buffer
 * \return   OK if successful, NOT_OK otherwise. BUSY_W if full and not forced
 * \todo
 */
base_t cbuff_pop(cbuff_handle_t cb, void *element, bool_t const rd_only);

/**
 * \brief    Provides the current number of elements in the circular buffer.
 * \param    cb - circular buffer to get its current
 * \return   size (number of elements), 0 if empty or NULL is provided
 * \todo
 */
uint16_t cbuff_size(cbuff_handle_t cb);

#endif /* CBUFF_H_ */