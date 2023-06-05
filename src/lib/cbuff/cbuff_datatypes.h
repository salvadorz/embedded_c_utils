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
  void    *vBuff;    // Will hold the buffer ref
  uint8_t  u8_eSize; // Element size
  bool_t   b_isFull; // if true the buffer is full
  uint16_t u16_lght; // Max length buffer capacity
  uint16_t u16_head; // tracks the location to insert (push)
  uint16_t u16_tail; // tracks the location to retrieve data (pop)

} cbuff_t;

#endif /* CBUFF_DATATYPES_H_ */