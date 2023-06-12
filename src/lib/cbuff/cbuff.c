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
 * @file cbuff.c
 * @author Salvador Z
 * @date 04 Jun 2023
 * @brief File for Circular buffer data structure (FIFO) implementation
 *
 * @see https://en.wikipedia.org/wiki/Circular_buffer
 */

#include "cbuff.h"
#include <string.h> // memcpy

static bool bfn_is_cbuff_empty(cbuff_handle_t cb) {
  bool ret_val = false;

  if ((cb->u16_head == cb->u16_tail) && !(cb->b_isFull)) {
    ret_val = true;
  }
  return ret_val;
}

base_t cbuff_init(cbuff_handle_t cb, void *const buffer, uint16_t const length, uint8_t const element_sz) {
  base_t ret_val = NOT_OK;

  if ((NULL != cb) && (NULL != buffer) && (length) && (element_sz)) {
    void    **buff_ref = (void **)&cb->vBuff;
    uint8_t  *elem_sz  = (uint8_t *)&cb->u8_eSize;
    uint16_t *buff_len = (uint16_t *)&cb->u16_lgth;

    // assignation of the members through pointers
    *buff_ref = buffer;
    *buff_len = length;
    *elem_sz  = element_sz;
    ret_val   = cbuff_reset(cb);
  }
  return ret_val;
}

base_t cbuff_reset(cbuff_handle_t cb) {
  base_t ret_val = NOT_OK;

  if (NULL != cb) {
    cb->u16_head = 0U;
    cb->u16_tail = 0U;
    cb->b_isFull = false;
    ret_val      = OK;
  }
  return ret_val;
}

base_t cbuff_push(cbuff_handle_t cb, void *const element, bool_t const forced) {
  base_t ret_val = OK;

  if ((NULL != cb) && (NULL != element) && (forced || !(cb->b_isFull))) {
    uint16_t head_cnt = cb->u16_head;
    char    *head_pt  = cb->vBuff + (head_cnt * cb->u8_eSize); // cb->vBuff[cb->u16_head] point to the head
    memcpy(head_pt, element, cb->u8_eSize);

    // move ahead the head idx, if reach max then it's value is 0
    cb->u16_head = (++head_cnt == cb->u16_lgth) ? 0U : head_cnt;

    if (forced && cb->b_isFull) { // if forced and full also move ahead the tail
      cb->u16_tail = (++cb->u16_tail == cb->u16_lgth) ? 0U : cb->u16_tail;
    }
    // update the full flag
    if (cb->u16_head == cb->u16_tail) cb->b_isFull = true;
  } else {
    ret_val = NOT_OK;
  }

  return ret_val;
}

base_t cbuff_pop(cbuff_handle_t cb, void *element, bool_t const rd_only) {
  base_t ret_val = OK;

  if ((NULL != cb) && !(bfn_is_cbuff_empty(cb))) {
    uint16_t tail_cnt = cb->u16_tail;
    char    *tail_pt  = cb->vBuff + (tail_cnt * cb->u8_eSize);
    memcpy(element, tail_pt, cb->u8_eSize);

    if (!rd_only) {
      // move ahead the tail idx, if reach max then it's value is 0
      cb->u16_tail = (++tail_cnt == cb->u16_lgth) ? 0U : tail_cnt;
      if (cb->b_isFull) cb->b_isFull = false;
    }
  } else {
    ret_val = NOT_OK;
  }

  return ret_val;
}

uint16_t cbuff_size(cbuff_handle_t cb) {
  uint16_t ret_val = 0U;

  if ((NULL != cb) && !(bfn_is_cbuff_empty(cb))) {
    int32_t elements = cb->u16_head - cb->u16_tail;

    if (0 > elements || cb->b_isFull) elements += cb->u16_lgth;

    ret_val = (uint16_t)elements;
  }

  return ret_val;
}
