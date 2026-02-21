#### **Abstract**

The `queue` module implements a generic First-In-First-Out (FIFO) queue with dynamic sizing.

#### **Functions and Usage**

1. **`queue_init(Queue *queue, size_t element_size)`**  
   Initializes a queue with a specified element size.  
   **Usage:**

   ```c
   queue_init(&queue, sizeof(int));
   ```

2. **`queue_push(Queue *queue, void *data)`**  
   Adds an element to the back of the queue.  
   **Usage:**

   ```c
   queue_push(&queue, &data);
   ```

3. **`queue_pop(Queue *queue)`**  
   Removes the front element of the queue.  
   **Usage:**

   ```c
   queue_pop(&queue);
   ```

4. **`queue_destroy(Queue *queue)`**  
   Frees memory used by the queue.  
   **Usage:**
   ```c
   queue_destroy(&queue);
   ```

#### Example usage

```c
#include <easyc/data_structures/queue.h>
#include <stdio.h>

int main() {
    Queue queue;
    queue_init(&queue, sizeof(int));

    int data1 = 10, data2 = 20, data3 = 30;

    queue_push(&queue, &data1);
    queue_push(&queue, &data2);
    queue_push(&queue, &data3);

    printf("Front: %d, Back: %d\n", *(int *)queue_front(&queue), *(int *)queue_back(&queue));

    queue_pop(&queue);
    printf("After pop, Front: %d\n", *(int *)queue_front(&queue));

    queue_destroy(&queue);
    return 0;
}
```
