# easyc

easyc is a C library designed to simplify working with data structures and string manipulation. It includes implementations such as dynamic arrays, stacks, queues, hash tables, and support for custom strings.

## Project Structure

```
├── includes          # Header files (.h)
│   ├── base_string.h
│   └── data_structures
│       ├── hashmap.h
│       ├── queue.h
│       ├── stack.h
│       └── vector.h
├── src               # Library implementation (.c)
│   ├── base_string.c
│   └── data_structures
│       ├── hashmap.c
│       ├── queue.c
│       ├── stack.c
│       └── vector.c
├── tests             # Unit tests
│   ├── base_string_test.c
│   └── data_structures
│       ├── hashmap_test.c
│       ├── queue_test.c
│       ├── stack_test.c
│       └── vector_test.c
├── Makefile          # Build configuration
├── Dockerfile        # Docker environment configuration
└── README.md         # Project documentation
```

## Features

- **String Manipulation**:
  - Create and destroy strings.
  - Convert to native C strings.
  - Query size and capacity.

- **Data Structures**:
  - Dynamic arrays.
  - Stacks.
  - Queues.
  - Hash tables.

## Installation

### Requirements

- GCC (or any compatible C compiler).
- Make.
- `check` library for unit testing.

### Installation Steps

1. Clone this repository:
   ```
   git clone https://gitlab.com/olooeez/easyc.git
   cd easyc
   ```

2. Compile the project:
   ```
   make
   ```

3. (Optional) Install the library on your system:
   ```
   sudo make install
   ```

## Tests

To run unit tests:

```
make test
```

The tests will run automatically, and the results will be displayed in the terminal.

## Usage

Include the necessary headers in your project and compile using the library paths:

```c
#include <easyc/base_string.h>
#include <easyc/data_structures/vector.h>
```

Compile with GCC flags:
```
gcc -o my_program my_program.c -I/usr/local/include/easyc -L/usr/local/lib/easyc -leasyc
```

## Contributing

1. Fork the project.
2. Create a branch for your changes: `git checkout -b my-feature`.
3. Push your changes: `git push origin my-feature`.
4. Open a Pull Request.

## License

This project is licensed under the [MIT License](https://gitlab.com/olooeez/easyc/-/blob/main/LICENSE).
