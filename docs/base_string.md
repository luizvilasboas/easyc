#### **Abstract**
The `base_string` module provides a custom string type with advanced manipulation capabilities such as dynamic resizing, substring operations, and concatenation.

#### **Functions and Usage**

1. **`string_create(const char *initial)`**  
   Creates a new `string` object initialized with the given value.  
   **Usage:**
   ```c
   string *str = string_create("Hello");
   ```

2. **`string_destroy(string *str)`**  
   Frees memory allocated for the string.  
   **Usage:**
   ```c
   string_destroy(str);
   ```

3. **`string_length(const string *str)`**  
   Returns the length of the string.  
   **Usage:**
   ```c
   size_t len = string_length(str);
   ```

4. **`string_concat(string *str, const char *suffix)`**  
   Appends a suffix to the string.  
   **Usage:**
   ```c
   string_concat(str, " World");
   ```

5. **`string_replace(string *str, const char *old_substring, const char *new_substring)`**  
   Replaces occurrences of a substring with another substring.  
   **Usage:**
   ```c
   string_replace(str, "World", "easyc");
   ```

#### Example usage

```c
#include <easyc/base_string.h>
#include <stdio.h>

int main() {
    string *str = string_create("Hello");
    printf("Initial string: %s\n", string_to_c(str));

    string_concat(str, ", World!");
    printf("Concatenated string: %s\n", string_to_c(str));

    printf("Length: %zu, Capacity: %zu\n", string_length(str), string_capacity(str));

    string_replace(str, "World", "easyc");
    printf("After replacement: %s\n", string_to_c(str));

    string_destroy(str);
    return 0;
}
```

