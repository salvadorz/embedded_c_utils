# Linked List

>:star: A linked list is a linear data structure that stores a collection of data elements dynamically.

Is the most sought-after data structure when it comes to handling dynamic data elements. A linked list consists of a data element known as a node. And each node consists of two fields: one field has data, and in the second field, the node has an address that keeps a reference to the next node.

## Design
[![linked_list](https://github-production-user-asset-6210df.s3.amazonaws.com/32500615/248528950-c5922809-b590-45ae-bd31-2c5900cf4e64.png)](https://github.com/salvadorz/embedded_c_utils/tree/develop/src/lib/llist "I'm a linked list! duh...")
> Linked list description

-------------
This is a generic linked list which can hold any custom and native datatype which implies two dynamic allocations. One for node structure and another to point(hold) to the data. The library frees the node memory after pop but assume the user will free the memory allocated after reception of the data reference.
It's designed as a LIFO structure, meaning data can be retrieved only from the head although there is an option to insert data at back but will be more expensive as head is the only element been tracked.
In order to provide a safe-easy usage some macros are provided, these macros simplify the usage of the linked list by defining a globally accessible handle (e.g., `llist_handle_t foo_handle`) and automatically managing the memory allocation and deallocation of the data reference.


## Lib `llist` API
This Linked list can hold any custom and native datatype has a macro which defines a global buffer (array) and its `cbuff` data structure type and initializes at the same time using `CBUFF_CREATE(datatype, buffer_name, buffer_length)`

The basic API (Macros) to use are:
| API CALL       | Description   |
| :-------------:|:--------------|
| **`LLIST_TYPE_CREATE`** | Defines a global handle and the needed functionality to handle the deallocation of memory|
| **`LLIST_POP_DATA`**  | Removes the node from the head and returns the data |
| **`LLIST_POP_REF`** | Removes the node from the head (*LIFO*). If empty/error returns `NOT_OK` |
| **`LLIST_PUSH_BACK`**  | Inserts a new node at the tail (*FIFO*). Increases the number of elements |
| **`LLIST_PUSH_FRONT`**  | Inserts a new node at the head (*LIFO*). Increases the number of elements |
| **`LLIST_TRAVERSE`** | Iterates on the list. receives a function pointer to perform some action on the data |

## Lib `llist` usage example

```c
#include "llist.h"

typedef struct my_struct {
  c_struct_t  complex;
  uint32_t data;
} my_struct_t;

/** Declaring my_struct_list global handle and the function(s) to handle freeing the memory */
LLIST_TYPE_CREATE(my_struct_t, my_struct_list);

int main(int argc, char *argv[]) {

    my_struct_t obj = { 0 };
    obj.data = argv[1];

    if (OK != LLIST_PUSH_FRONT(obj, my_struct_list)) {
      printf("Failed to push data %d\n", obj.data);
    } else {
      printf("Pushed data: %d linked list has %d elements\n", obj.data, llist_get_size(my_struct_list));
    }
    // do stuff
    if (OK == LLIST_POP_REF(my_struct_list, &obj)) {
      printf("Popped data:%d, linked list has %d elements\n", obj.data, llist_get_size(my_struct_list));
    } else
      printf("Failed to pop, empty?");
    return OK;
}
```

## Contributing :smiley:

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.