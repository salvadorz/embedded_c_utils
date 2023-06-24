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
 * @file llist.c
 * @author Salvador Z
 * @date 23 Jun 2023
 * @brief File for Linked list implementation
 */

#include "llist.h"
#include <stdlib.h> /*malloc, free*/

static base_t llist_allocate_node(ll_node_ptr_t *new_node) {
  base_t ret_val = OK;

  *new_node = (ll_node_ptr_t)malloc(sizeof(ll_node_t));

  if (NULL == *new_node) {
    ret_val = NOT_OK;
  }

  return ret_val;
}

ll_node_ptr_t llist_create_node(void *data, uint32_t data_size) {

  ll_node_t *new_node = NULL;

  if ((NULL != data) && (0 != data_size) && (OK == llist_allocate_node(&new_node))) {

    new_node->data = malloc(data_size);

    if (NULL != new_node->data) {
      for (uint32_t i = 0; i < data_size; ++i) {
        *((uint8_t *)new_node->data + i) = *((uint8_t *)data + i);
      } // memcpy(new_node->data, data, data_size);
      new_node->next = NULL;
    } else {
      free(new_node);
      new_node = NULL; // Avoid dangling pointer
    }
  }

  return new_node;
}

base_t llist_push_head(ll_handle_t *head, ll_node_ptr_t node) {
  base_t ret_val = OK;

  // *head could be NULL if this is the first push
  if (NULL != node) {
    node->next = *head;
    *head      = node; // Node is the new head
  } else {
    ret_val = NOT_OK;
  }

  return ret_val;
}

base_t llist_push_tail(ll_handle_t *head, ll_node_ptr_t node) {
  base_t ret_val = OK;

  if (NULL != node) {
    if (NULL == *head) {
      *head = node;
    } else {
      ll_node_ptr_t current = *head;
      // find the tail
      while (NULL != current->next) {
        current = current->next;
      }
      current->next = node;
    }
  } else {
    ret_val = NOT_OK;
  }

  return ret_val;
}

base_t llist_pop_head_refd(ll_handle_t *head, void **data) {
  base_t ret_val = OK;

  if (NULL != *head) {
    ll_node_t *node = *head;

    *data = (*head)->data;
    *head = (*head)->next;
    free(node); // node->data needs to be freed by the user
  } else {
    ret_val = NOT_OK;
  }

  return ret_val;
}

void *llist_pop_head_data(ll_handle_t *head) {
  void *data = NULL;

  if (NULL != *head) {
    ll_node_t *node = *head;

    data  = (*head)->data;
    *head = (*head)->next;
    free(node);
  }

  return data; // needs to be freed by the user
}

inline static void llist_delete_node(ll_node_ptr_t node) {
  free(node->data);
  free(node);
  node = NULL;
}

void llist_delete_list(ll_handle_t *head) {
  ll_node_ptr_t current = *head;

  while (NULL != *head) {
    current = *head;
    *head   = (*head)->next;
    llist_delete_node(current);
  }
}

base_t llist_reversal(ll_handle_t *head) {
  base_t ret_val = OK;

  if (NULL != *head) {
    ll_node_ptr_t prev = NULL;
    ll_node_ptr_t next = *head;

    while (NULL != next) {
      *head         = next;
      next          = next->next;
      (*head)->next = prev;
      prev          = *head;
    }

  } else {
    ret_val = NOT_OK;
  }

  return ret_val;
}

uint32_t llist_get_size(ll_handle_t head) {
  uint32_t size = 0;

  while (NULL != head) {
    ++size;
    head = head->next;
  }

  return size;
}

void llist_print(ll_handle_t const head, void (*vfn_ptr)(void *)) {
  ll_node_ptr_t node_ref = head;

  while (NULL != node_ref) {
    (*vfn_ptr)(node_ref->data);

    node_ref = node_ref->next;
  }
  (*vfn_ptr)(NULL); // Notify the end of the list
}