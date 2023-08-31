/**
 * @file llist_datatypes.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Linked List Data Types
 *
 */

#ifndef LLIST_DATATYPES_H_
#define LLIST_DATATYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

// Includes
#include "utils_common.h"

typedef struct ll_node_s ll_node_t;

typedef ll_node_t *ll_handle_t;
typedef ll_node_t *ll_node_ptr_t;

struct ll_node_s {
  ll_node_t *next;
  void      *data; // Any data type
};

typedef struct sl_list {
    ll_handle_t head;
    ll_handle_t tail;
} sl_list_t;
/*
typedef struct sl_node_s sl_node_t;
typedef struct sl_list_s sl_list_t;

struct sl_node_s {
  sl_node_t *next;
};

struct sl_list_s {
  sl_node_t *head;
};
*/

#ifdef __cplusplus
}
#endif

#endif /* LLIST_DATATYPES_H_ */