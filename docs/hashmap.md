#### **Abstract**

The `hashmap` module implements a hash map with user-defined hash and comparison functions, allowing efficient storage and retrieval of key-value pairs.

#### **Functions and Usage**

1. **`hashmap_init(HashMap *map, size_t bucket_count, size_t key_size, size_t value_size, hash_fn, cmp_fn)`**  
   Initializes a hash map with the specified parameters.  
   **Usage:**

   ```c
   hashmap_init(&map, 10, sizeof(char *), sizeof(int), hash_fn, cmp_fn);
   ```

2. **`hashmap_insert(HashMap *map, void *key, void *data)`**  
   Inserts a key-value pair into the map.  
   **Usage:**

   ```c
   hashmap_insert(&map, "key", &value);
   ```

3. **`hashmap_get(HashMap *map, void *key)`**  
   Retrieves the value associated with a key.  
   **Usage:**

   ```c
   int *value = hashmap_get(&map, "key");
   ```

4. **`hashmap_destroy(HashMap *map)`**  
   Frees resources used by the hash map.  
   **Usage:**
   ```c
   hashmap_destroy(&map);
   ```

#### Example usage

```c
#include <libstd/data_structures/hashmap.h>
#include <stdio.h>
#include <string.h>

unsigned long hash_fn(void *key) {
    char *str = (char *)key;
    unsigned long hash = 5381;
    while (*str)
        hash = ((hash << 5) + hash) + *str++;
    return hash;
}

int cmp_fn(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

int main() {
    HashMap map;
    hashmap_init(&map, 10, sizeof(char *), sizeof(int), hash_fn, cmp_fn);

    int value = 42;
    char *key = "example";

    hashmap_insert(&map, key, &value);

    int *retrieved_value = hashmap_get(&map, key);
    if (retrieved_value) {
        printf("Value for key '%s': %d\n", key, *retrieved_value);
    }

    hashmap_destroy(&map);
    return 0;
}
```
