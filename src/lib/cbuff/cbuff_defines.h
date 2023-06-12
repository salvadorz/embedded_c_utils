/**
 * @file cbuff_defines.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Circular buffer definitions and macros
 *
 */

#ifndef CBUFF_DEFINES_H_
#define CBUFF_DEFINES_H_

// clang-format off

#define __CBUFF_TYPE(type, buff, size)  \
  type buff ## cbuff[size];             \
  cbuff_t buff = {                      \
    .vBuff = buff ## cbuff,             \
    .u8_eSize = sizeof(type),           \
    .b_isFull = false,                  \
    .u16_lgth = size,                   \
    .u16_head = 0U,                     \
    .u16_tail = 0U,                     \
  };

#define _CBUFF_DEF_TYPE(type, buff, size)  \
        __CBUFF_TYPE(type, buff, size)     \
    base_t buff ## _push_refd(type *pt)    \
    {                                      \
        return cbuff_push(&buff, pt, 0);   \
    }                                      \
    base_t buff ## _push_ovwr(type *pt)    \
    {                                      \
        return cbuff_push(&buff, pt, 1);   \
    }                                      \
    base_t buff ## _pop_refd(type *pt)     \
    {                                      \
        return cbuff_pop(&buff, pt, 0);    \
    }                                      \
    base_t buff ## _get_refd(type *pt)     \
    {                                      \
        return cbuff_pop(&buff, pt, 1);    \
    }
// clang-format on
#endif /* CBUFF_DEFINES_H_ */