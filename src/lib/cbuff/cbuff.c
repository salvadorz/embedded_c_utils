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

  if (cb->u16_head == cb->u16_tail) {
    ret_val = true;
  }
  return ret_val;
}

base_t cbuff_init(cbuff_handle_t cb, void *const buffer, uint16_t const length, uint8_t const element_sz) {
  base_t ret_val = NOT_OK;

  if ((NULL != cb) && (NULL != buffer) && (length) && (element_sz)) {
    void    **buff_ref = (void **)&cb->vBuff;
    uint16_t *elem_sz  = (uint16_t *)&cb->u16_eSize;
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
    ret_val      = OK;
  }
  return ret_val;
}

base_t cbuff_push(cbuff_handle_t cb, void *const element, bool_t const forced) {
  base_t ret_val = OK;

  if ((NULL == cb) || (NULL == element)) {
    ASSERT(cb && element);
    ret_val = NOT_OK;
  } else {
    uint16_t const buff_lgth = cb->u16_lgth;
    bool_t const   buff_full = (buff_lgth <= cbuff_size(cb)) ? true : false;

    // if the push is forced or check if there is space on the buffer
    if (forced || (!buff_full)) {
      uint16_t head_cnt = cb->u16_head;
      char    *head_pt  = cb->vBuff + ((head_cnt % buff_lgth) * cb->u16_eSize); // cb->vBuff[cb->u16_head]
      (void)memcpy(head_pt, element, cb->u16_eSize);

      // move ahead the head idx, if reach max then it's value is 0
      cb->u16_head = (++head_cnt >= (buff_lgth << 1)) ? 0U : head_cnt;

      if (forced && buff_full) {
        // if full then move ahead the tail
        cb->u16_tail = (++cb->u16_tail >= (buff_lgth << 1)) ? 0U : cb->u16_tail;
      }
    } else {
      ret_val = BUSY_W;
    }
  }

  return ret_val;
}

base_t cbuff_pop(cbuff_handle_t cb, void *element, bool_t const rd_only) {
  base_t ret_val = OK;

  if ((NULL != cb) && (NULL != element) && !(bfn_is_cbuff_empty(cb))) {
    uint16_t const buff_lgth = cb->u16_lgth;

    uint16_t tail_cnt = cb->u16_tail;
    char    *tail_pt  = cb->vBuff + ((tail_cnt % buff_lgth) * cb->u16_eSize);
    (void)memcpy(element, tail_pt, cb->u16_eSize);

    if (!rd_only) {
      // move ahead the tail idx, if reach max then it's value is 0
      cb->u16_tail = (++tail_cnt >= (buff_lgth << 1)) ? 0U : tail_cnt;
    }
  } else {
    ret_val = NOT_OK;
  }

  return ret_val;
}

uint16_t cbuff_size(cbuff_handle_t cb) {
  uint16_t ret_val = 0U;

  if (NULL != cb) {
    int32_t elements = cb->u16_head - cb->u16_tail;

    if (0 > elements) elements += (cb->u16_lgth << 1);

    ret_val = (uint16_t)elements;
  }

  return ret_val;
}
