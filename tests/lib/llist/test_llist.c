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
 * @file test_llist.c
 * @author Salvador Z
 * @date 24 Jun 2023
 * @brief File for testing the llist library.
 */

#include "llist.h"
#include "uTest.h"
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free*/

#define MAX_LLIST_LEN 10

typedef struct my_struct {
  uint8_t  dummy;
  uint32_t data;
} my_struct_t;

static void print_my_struct(void *s) {
  if (NULL == s) {
    printf("-{nil}\n");
  } else {
    printf("[%d]", (int)((my_struct_t *)(s))->data);
  }
}

void test_llist_no_macros() {
  my_struct_t obj  = { 0 };
  ll_handle_t head = NULL;

  for (uint32_t i = 0; i < MAX_LLIST_LEN; ++i) {
    obj.data = i + 1;
    TEST_ASSERT_EQUAL_VAL_MSG(OK, llist_push_head(&head, llist_create_node(&obj, sizeof(my_struct_t))),
                              "Failed to push head");
  }
  TEST_ASSERT_EQUAL_VAL_MSG(MAX_LLIST_LEN, llist_get_size(head),
                            "llist shall be holding MAX_LLIST_LEN (10) elements");
  llist_traverse(head, print_my_struct);
  TEST_ASSERT_EQUAL_VAL_MSG(OK, llist_reversal(&head), "Failed to reverse list");

  for (uint32_t i = 0; i < MAX_LLIST_LEN; ++i) {
    my_struct_t *ret = (my_struct_t *)llist_pop_head_data(&head);
    TEST_ASSERT_EQUAL_VAL_MSG(i + 1, ret->data, "Failed to pop head");
    free(ret);
    TEST_ASSERT_EQUAL_VAL_MSG((MAX_LLIST_LEN - 1) - i, llist_get_size(head),
                              "llist shall be decreasing it's elements");
  }
  TEST_ASSERT_EQUAL_VAL_MSG(0, llist_get_size(head), "llist shall be empty");
  TEST_ASSERT_EQUAL_MSG(NULL, llist_pop_head_data(&head), "llist is empty, shall return NULL");
  llist_delete_list(&head);
}

void test_llist_tail_no_macros() {
  my_struct_t obj  = { 0 };
  ll_handle_t head = NULL;

  for (uint32_t i = 0; i < MAX_LLIST_LEN; ++i) {
    obj.data = i + 1;
    TEST_ASSERT_EQUAL_VAL_MSG(OK, llist_push_tail(&head, llist_create_node(&obj, sizeof(my_struct_t))),
                              "Failed to push head");
  }
  TEST_ASSERT_EQUAL_VAL_MSG(MAX_LLIST_LEN, llist_get_size(head),
                            "llist shall be holding MAX_LLIST_LEN (10) elements");
  llist_traverse(head, print_my_struct);
  TEST_ASSERT_EQUAL_VAL_MSG(OK, llist_reversal(&head), "Failed to reverse list");

  for (uint32_t i = 0; i < MAX_LLIST_LEN; ++i) {
    my_struct_t *ret = (my_struct_t *)llist_pop_head_data(&head);
    if (NULL == ret) {
      llist_delete_list(&head);
      TEST_ASSERT_FAIL("ERROR: pop_head_data shall not return NULL");
    }
    TEST_ASSERT_EQUAL_VAL_MSG(MAX_LLIST_LEN - i, ret->data, "Failed to pop head");
    free(ret);
    TEST_ASSERT_EQUAL_VAL_MSG((MAX_LLIST_LEN - 1) - i, llist_get_size(head),
                              "llist shall be decreasing it's elements");
  }
  TEST_ASSERT_EQUAL_VAL_MSG(0, llist_get_size(head), "llist shall be empty");
  TEST_ASSERT_EQUAL_MSG(NULL, llist_pop_head_data(&head), "llist is empty, shall return NULL");
  llist_delete_list(&head);
}

/** Declaring my_struct_list global handle and the function(s) to handle freeing the memory */
LLIST_TYPE_CREATE(my_struct_t, my_struct_list);

void test_llist_with_macros() {
  my_struct_t obj = { 0 };

  for (uint32_t i = 0; i < MAX_LLIST_LEN; ++i) {
    obj.data = i + 1;
    TEST_ASSERT_EQUAL_VAL_MSG(OK, LLIST_PUSH_FRONT(obj, my_struct_list), "Failed to push head");
  }
  TEST_ASSERT_EQUAL_VAL_MSG(MAX_LLIST_LEN, llist_get_size(my_struct_list),
                            "llist shall be holding MAX_LLIST_LEN (10) elements");
  llist_traverse(my_struct_list, print_my_struct);
  TEST_ASSERT_EQUAL_VAL_MSG(OK, llist_reversal(&my_struct_list), "Failed to reverse list");

  /** Now using POP_REF DATA */
  for (uint32_t i = 0; i < MAX_LLIST_LEN; ++i) {
    my_struct_t ret = { 0 };
    TEST_ASSERT_EQUAL_VAL_MSG(OK, LLIST_POP_REF(my_struct_list, &ret), "Failed to pop head");
    TEST_ASSERT_EQUAL_VAL_MSG(i + 1, ret.data, "Increasing values...");
    TEST_ASSERT_EQUAL_VAL_MSG((MAX_LLIST_LEN - 1) - i, llist_get_size(my_struct_list),
                              "llist shall be decreasing it's elements");
  }
  TEST_ASSERT_EQUAL_VAL_MSG(0, llist_get_size(my_struct_list), "llist shall be empty");
  TEST_ASSERT_EQUAL_MSG(NULL, llist_pop_head_data(&my_struct_list), "llist is empty, shall return NULL");
  TEST_ASSERT_EQUAL_MSG(NOT_OK, LLIST_POP_REF(my_struct_list, &obj), "llist is empty, shall return NOT_OK");

  // Now fill the list again, but this time with push tail
  for (uint32_t i = 0; i < MAX_LLIST_LEN; ++i) {
    obj.data = i + 1;
    TEST_ASSERT_EQUAL_VAL_MSG(OK, LLIST_PUSH_BACK(obj, my_struct_list), "Failed to push head");
  }

  TEST_ASSERT_EQUAL_VAL_MSG(MAX_LLIST_LEN, llist_get_size(my_struct_list),
                            "llist shall be holding MAX_LLIST_LEN (10) elements");
  TEST_ASSERT_EQUAL_VAL_MSG(OK, llist_reversal(&my_struct_list), "Failed to reverse list");
  TEST_ASSERT_EQUAL_VAL_MSG(OK, llist_reversal(&my_struct_list), "Failed to reverse list");
  TEST_ASSERT_EQUAL_VAL_MSG(MAX_LLIST_LEN, llist_get_size(my_struct_list),
                            "llist shall be holding MAX_LLIST_LEN (10) elements");
  llist_traverse(my_struct_list, print_my_struct);

  /** Now using POP_DATA */
  for (uint32_t i = 0; i < MAX_LLIST_LEN; ++i) {
    my_struct_t ret = LLIST_POP_DATA(my_struct_list);
    TEST_ASSERT_EQUAL_VAL_MSG(i + 1, ret.data, "Increasing values...");
    TEST_ASSERT_EQUAL_VAL_MSG((MAX_LLIST_LEN - 1) - i, llist_get_size(my_struct_list),
                              "llist shall be decreasing it's elements");
  }
}

void test_llist_errors_and_delete() {
  my_struct_t obj  = { 0 };
  ll_handle_t head = NULL;

  for (uint32_t i = 0; i < MAX_LLIST_LEN; ++i) {
    obj.data = i + 1;
    TEST_ASSERT_EQUAL_VAL_MSG(OK, llist_push_head(&head, llist_create_node(&obj, sizeof(my_struct_t))),
                              "Failed to push head");
  }
  llist_delete_list(&head);

  TEST_ASSERT_EQUAL_VAL_MSG(0, llist_get_size(head), "llist must be empty");
  TEST_ASSERT_EQUAL_VAL_MSG(NOT_OK, llist_push_head(&head, NULL), "Need to fail as node is NULL");
  TEST_ASSERT_EQUAL_VAL_MSG(NOT_OK, llist_push_tail(&head, NULL), "Need to fail as node is NULL");
  TEST_ASSERT_EQUAL_VAL_MSG(NOT_OK, llist_reversal(&head), "Reversing empty list shall fail");

}

int main() {
  uTEST_INIT("test_llist.c");
  uTEST_ADD_MSG(test_llist_no_macros, "Linked list test with no macros");
  uTEST_ADD_MSG(test_llist_tail_no_macros, "Linked list test with no macros pushed to tail");
  uTEST_ADD_MSG(test_llist_with_macros,
                "List test with macros, no need to freed memory or declare the handle");
  uTEST_ADD_MSG(test_llist_errors_and_delete, "Linked list testing errors and delete");
  return (uTEST_END());
}
