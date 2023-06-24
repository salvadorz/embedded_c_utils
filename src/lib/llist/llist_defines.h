/**
 * @file llist_defines.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Linked list macro definitions
 *
 */

#ifndef LLIST_DEFINES_H_
#define LLIST_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define _LLIST_DEF_TYPE(type, list)                                 \
  type llist_pop_head_data_##list(ll_handle_t *head) {              \
    type *_ptr = (type *)llist_pop_head_data(head);                 \
    type  ret  = { 0 };                                             \
    if (NULL != _ptr) ret = *_ptr;                                  \
    free(_ptr);                                                     \
    return ret;                                                     \
  }                                                                 \
  base_t llist_pop_head_refd_##list(ll_handle_t *head, type *ref) { \
    void  *_ptr = NULL;                                             \
    base_t ret  = llist_pop_head_refd(head, &_ptr);                 \
    if (0 == ret) *ref = *(type *)_ptr;                             \
    free(_ptr);                                                     \
    return ret;                                                     \
  }                                                                 \
  ll_handle_t list = NULL

#ifdef __cplusplus
}
#endif

#endif /* LLIST_DEFINES_H_ */