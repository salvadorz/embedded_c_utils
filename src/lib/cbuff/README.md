# Circular buffer

Is a data structure (FIFO) that uses a single, fixed-size buffer as if it were connected end-to-end. This structure lends itself easily to buffering data streams

## Lib `cbuff` usage
With embedded systems on mind this implementation avoids dynamic memory allocation. Instead has a macro which defines a global buffer (array) and its `cbuff` data structure type and initializes at the same time using `CBUFF_CREATE(datatype, buffer_name, buffer_length)`

The basic API (Macros) to use are:
| API CALL       | Description   |
| -------------- |:-------------:|
| **`CBUFF_CREATE`** | Initialize the cbuff structure, defines the buffer |
| **`CBUFF_PUT`**  | Inserts a new data into the *CBUFF* (FIFO) |
| **`CBUFF_PUSH`** | Inserts a new data into the *CBUFF* (FIFO). If full then overwrites the _oldest data_ |
| **`CBUFF_GET`**  | Copies the _oldest_ data from the *CBUFF* (FIFO). Do not decrease the number of elements |
| **`CBUFF_POP`**  | Retrieves the _oldest_ data from the *CBUFF* (FIFO) and decrease by one the number of elements in the buffer |
| **`CBUFF_FLUSH`** | Resets the Circular Buffer by putting it in a known state. *Does not clean the freed slots* |

## Lib `cbuff` usage example

```c
#include "cbuff.h"

#define BUFFER_SIZE (5U)

CBUFF_CREATE(int, int_cb, BUFFER_SIZE)

int main(int argc, char *argv[]) {

    data = 30;

    if (NOT_OK == CBUFF_PUSH(int_cb, &data)) {
      printf("Failed to push data %d\n", data);
    } else {
      printf("Pushed data: %d cbuff still has %d free elements\n", data, CBUFF_FREE_SPACES(int_cb));
    }

    if (OK == CBUFF_POP(int_cb, &data)) {
      printf("Popped data:%d, cbuff has %d free elements\n", data, CBUFF_FREE_SPACES(int_cb));
    } else
      printf("Failed to pop, empty?");
    return OK;
}
```

## Considerations
The current implementation can be used with the macros which will take care of initialize and the flags on *push* or *pop*.

![Circular buffer](https://upload.wikimedia.org/wikipedia/commons/thumb/f/fd/Circular_Buffer_Animation.gif/400px-Circular_Buffer_Animation.gif)

To detect the buffer capacity on the **empty** case you can check if the *pop_idx tracker* and the *push_idx tracker* are pointing to the same location. That implies the **full** state is when the `push_idx + 1 == pop_idx `but this will lead to _waste_ one slot from the buffer. One solution is to add a flag in order to show/detect the **full** case.

### Thread Safety
Usually the producer (`push`) and the consumer (`pop`) modifies only one of the index making the circular buffer *thread-safe* by nature. But when introducing the full-flag implies a _mutual exclusion_ ([_design_](https://www.codeproject.com/Articles/43510/Lock-Free-Single-Producer-Single-Consumer-Circular#heading_atomic_operations)) requirement because the flag will be shared between this two threads (consumer and producer).

## More Info
[Ring buffer basics](https://www.embedded.com/ring-buffer-basics/)

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.
