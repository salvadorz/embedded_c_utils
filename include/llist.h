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
 * @file llist.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Linked list API
 *
 */

#ifndef LLIST_H_
#define LLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

// Includes
#include "llist_datatypes.h"
#include "llist_defines.h"

/**
 * Description:
 *   Defines globally a handle for the linked list of a given type.
 *    The type can be native data types or user-defined data types.
 *
 * Usage:
 *   LLIST_TYPE_CREATE(uint8_t, u8_list_head);
 *   LLIST_TYPE_CREATE(struct foo, list_foo_head);
 *   LLIST_PUSH_FRONT(u8_data, u8_list_head);
 *   uint8_t u8_data = LLIST_POP_DATA(u8_list_head);
 */
#define LLIST_TYPE_CREATE(type, handle) _LLIST_DEF_TYPE(type, handle)

/**
 * Description:
 *   Removes the node at the head of the linked list and returns the data
 */
#define LLIST_POP_DATA(list) llist_pop_head_data_##list((&list))

/**
 * Description:
 *   Removes the node at the head of the linked list and provides the data in/out reference
 *
 * Returns (base_t):
 *   0 - Success
 *   1 - Error
 */
#define LLIST_POP_REF(list, ref) llist_pop_head_refd_##list((&list), ref)

/**
 * Description:
 *   Inserts the value holded by `val` at the back of the linked list.
 *
 * Returns (base_t):
 *   0 - Success
 *   1 - Error
 */
#define LLIST_PUSH_BACK(val, list) llist_push_tail(&list, llist_create_node(&val, sizeof(val)))

/**
 * Description:
 *   Inserts the value holded by `val` at the head of the linked list.
 *
 * Returns (base_t):
 *   0 - Success
 *   1 - Error
 */
#define LLIST_PUSH_FRONT(val, list) llist_push_head(&list, llist_create_node(&val, sizeof(val)))

/**
 * \brief    Creates a node for the linked list and fills it with the data provided
 * \param    data - to be copied into the node
 * \param    data_size - to be allocated in the node
 * \return   the node created
 * \todo
 */
ll_node_ptr_t llist_create_node(void *data, uint32_t data_size);

/**
 * \brief    Insert a node at the head of the list and updates the head
 * \param    head - reference (double pointer) to the head of the list, updated after the insertion
 * \param    node - reference to the node to be inserted
 * \return   - OK if the insertion was successful, NOT_OK otherwise
 * \todo
 */
base_t llist_push_head(ll_handle_t *head, ll_node_ptr_t node);

/**
 * \brief    Insert a node at the tail of the list and updates the head if the list was empty
 * \param    head - reference (double pointer) to the head of the list
 * \param    node - reference to the node to be inserted (append)
 * \return   - OK if the insertion was successful, NOT_OK otherwise
 * \todo
 */
base_t llist_push_tail(ll_handle_t *head, ll_node_ptr_t node);

/**
 * \brief    Retrieve data from the head of the list and updates the head
 * \param    head - reference (double pointer) to the head of the list
 * \param    data - reference to the data to be retrieved
 * \return   - OK if the retrieve was successful, NOT_OK otherwise
 * \todo
 */
base_t llist_pop_head_refd(ll_handle_t *head, void **data);

/**
 * \brief    Retrieves data from the head of the list and updates the head
 * \param    head - reference (double pointer) to the head of the list
 * \return   a reference to the data retrieved. **Must be freed by user** NULL if the list is empty.
 * \todo
 */
void *llist_pop_head_data(ll_handle_t *head);

/**
 * \brief    Deletes the list and frees the memory, the head is set to NULL
 * \param    head - reference (double pointer) to the head of the list
 */
void llist_delete_list(ll_handle_t *head);

/**
 * \brief    Reverses a list and updates the head
 * \param    head - reference (double pointer) to the head of the list
 */
base_t llist_reversal(ll_handle_t *head);

/**
 * \brief    Returns the size of the list
 * \param    head - reference to the head of the list
 * \return   the size of the list
 */
uint32_t llist_get_size(ll_handle_t head);

/**
 * \brief    Calls the function provided to perform an action on the data in the list, when the list ends
 *           or is empty it provides NULL to the function as notification.
 * \param    head - reference to the head of the list
 * \param    vfn_ptr - pointer to the function that prints the data
 */
void llist_traverse(ll_handle_t const head, void (*vfn_ptr)(void *));

/**
 * @brief Appends an element to the list, It updates the Head and tail of the list
 * 
 * @param singly_linked_list 
 * @param node_data 
 * @return base_t 
 */
base_t sl_list_insert(sl_list_t **singly_linked_list, void *node_data, uint32_t data_size);
// base_t sl_list_insert(sl_list_t **singly_linked_list, int node_data);

#ifdef __cplusplus
}
#endif

#endif /* LLIST_H_ */