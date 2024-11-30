#### **Abstract**
The `vector` module implements a dynamic array (vector) for efficient sequential storage of elements.

#### **Functions and Usage**

1. **`vector_init(Vector *vector, size_t element_size)`**  
   Initializes a vector for elements of the specified size.  
   **Usage:**
   ```c
   vector_init(&vector, sizeof(int));
   ```

2. **`vector_insert(Vector *vector, void *data)`**  
   Inserts an element into the vector.  
   **Usage:**
   ```c
   vector_insert(&vector, &data);
   ```

3. **`vector_remove(Vector *vector, size_t index)`**  
   Removes an element at the specified index.  
   **Usage:**
   ```c
   vector_remove(&vector, 0);
   ```

4. **`vector_destroy(Vector *vector)`**  
   Frees memory allocated for the vector.  
   **Usage:**
   ```c
   vector_destroy(&vector);
   ```

#### Example usage

```c
#include <easyc/data_structures/vector.h>
#include <stdio.h>

int compare_ints(void *a, void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    Vector vector;
    vector_init(&vector, sizeof(int));

    int data1 = 5, data2 = 2, data3 = 8;

    vector_insert(&vector, &data1);
    vector_insert(&vector, &data2);
    vector_insert(&vector, &data3);

    printf("Vector size: %d\n", vector_size(&vector));

    vector_sort(&vector, compare_ints);

    for (size_t i = 0; i < vector_size(&vector); i++) {
        printf("Element %zu: %d\n", i, *(int *)vector_get(&vector, i));
    }

    vector_destroy(&vector);
    return 0;
}
```
