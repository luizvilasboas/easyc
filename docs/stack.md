#### **Abstract**

The `stack` module implements a Last-In-First-Out (LIFO) stack with generic data type support.

#### **Functions and Usage**

1. **`stack_init(Stack *stack, size_t element_size)`**  
   Initializes a stack for elements of the specified size.  
   **Usage:**

   ```c
   stack_init(&stack, sizeof(int));
   ```

2. **`stack_push(Stack *stack, void *data)`**  
   Pushes an element onto the stack.  
   **Usage:**

   ```c
   stack_push(&stack, &data);
   ```

3. **`stack_pop(Stack *stack)`**  
   Removes the top element from the stack.  
   **Usage:**

   ```c
   stack_pop(&stack);
   ```

4. **`stack_destroy(Stack *stack)`**  
   Frees memory allocated for the stack.  
   **Usage:**
   ```c
   stack_destroy(&stack);
   ```

#### Example usage

```c
#include <libstd/data_structures/stack.h>
#include <stdio.h>

int main() {
    Stack stack;
    stack_init(&stack, sizeof(int));

    int data1 = 1, data2 = 2, data3 = 3;

    stack_push(&stack, &data1);
    stack_push(&stack, &data2);
    stack_push(&stack, &data3);

    printf("Top of stack: %d\n", *(int *)stack_top(&stack));

    stack_pop(&stack);
    printf("After pop, Top: %d\n", *(int *)stack_top(&stack));

    stack_destroy(&stack);
    return 0;
}
```
