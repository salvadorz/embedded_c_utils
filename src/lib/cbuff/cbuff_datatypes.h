/**
 * @file cbuff_datatypes.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Circular/ring buffer datatypes definition
 *
 */

#ifndef CBUFF_DATATYPES_H_
#define CBUFF_DATATYPES_H_

// Includes
#include "utils_common.h"

typedef struct cbuff_s {
  void *const    vBuff;     // Will hold the buffer ref
  uint16_t const u16_eSize; // Element size
  uint16_t const u16_lgth;  // Max length buffer capacity can't be < UINT16_MAX / 2
  uint16_t       u16_head;  // tracks the location to insert (push)
  uint16_t       u16_tail;  // tracks the location to retrieve data (pop)

} cbuff_t;

#endif /* CBUFF_DATATYPES_H_ */