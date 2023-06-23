#include "cbuff.h"
#include "uTest.h"

#define BUFFER_SIZE (5)

typedef struct my_structs {
  uint8_t  dummy;
  uint32_t data;
} my_struct_t;

CBUFF_CREATE(my_struct_t, my_cb, BUFFER_SIZE);

void fn_test_my_cbuff(void) {
  my_struct_t obj = { 0 };
  for (int i = 0; i < BUFFER_SIZE; ++i) {
    ++obj.data;
    TEST_ASSERT_EQUAL_VAL(OK, CBUFF_PUT(my_cb, &obj));
    TEST_ASSERT_EQUAL_VAL((BUFFER_SIZE - 1) - i, CBUFF_SPACES(my_cb));
  }
  // The Buffer should be full
  TEST_ASSERT_EQUAL_VAL(BUSY_W, CBUFF_PUT(my_cb, &obj));
  TEST_ASSERT_EQUAL_VAL(0, CBUFF_SPACES(my_cb));

  for (int i = 0; i < BUFFER_SIZE; ++i) {
    TEST_ASSERT_EQUAL_VAL(OK, CBUFF_POP(my_cb, &obj));
    TEST_ASSERT_EQUAL_VAL(i + 1, obj.data);
  }

  // The Buffer should be empty
  TEST_ASSERT_EQUAL_VAL(NOT_OK, CBUFF_POP(my_cb, &obj));
  TEST_ASSERT_EQUAL_VAL(BUFFER_SIZE, CBUFF_SPACES(my_cb));
}

void fn_test_cbuff_iterations(void) {
  my_struct_t obj    = { 0 };
  uint32_t    popCmp = 0;
  for (int i = 1; i <= BUFFER_SIZE * 3; ++i) {
    obj.data = i;
    if ((BUFFER_SIZE * 3) - 1 == i) {
      TEST_ASSERT_EQUAL_VAL(BUSY_W, CBUFF_PUT(my_cb, &obj));
    } else {
      TEST_ASSERT_EQUAL_VAL(OK, CBUFF_PUT(my_cb, &obj));
    }

    if (0 == (i % 2)) {
      ++popCmp;
      TEST_ASSERT_EQUAL_VAL(OK, CBUFF_POP(my_cb, &obj));
      TEST_ASSERT_EQUAL_VAL(popCmp, obj.data);
    }

    if (0 == (i % 5)) {
      ++popCmp;
      TEST_ASSERT_EQUAL_VAL(OK, CBUFF_POP(my_cb, &obj));
      TEST_ASSERT_EQUAL_VAL(popCmp, obj.data);
    }
  } /*end_for*/
}

void fn_test_cbuff_overwrite(void) {
  my_struct_t obj = { 0 };
  for (int i = 1; i <= BUFFER_SIZE * 2; ++i) {
    obj.data = i;
    TEST_ASSERT_EQUAL_VAL(OK, CBUFF_PUSH(my_cb, &obj));
  }
  for (int i = 1; i <= BUFFER_SIZE; ++i) {
    TEST_ASSERT_EQUAL_VAL(OK, CBUFF_POP(my_cb, &obj));
    TEST_ASSERT_EQUAL_VAL((BUFFER_SIZE + i), obj.data);
  }
}

int main() {
  uTEST_INIT("test_cbuff.c");
  // uTEST_START();
  uTEST_ADD_MSG(fn_test_my_cbuff, "Circular Buffer test simple", 15);
  uTEST_ADD_MSG(fn_test_cbuff_iterations, "Circular Buffers test iterations");
  uTEST_ADD_MSG(fn_test_cbuff_overwrite, "Circular Buffers test with push forced", 59);
  return (uTEST_END());
}