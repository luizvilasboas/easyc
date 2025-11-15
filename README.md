# easyc

> A C library designed to simplify working with common data structures and string manipulation.

## About the Project

`easyc` is a library written in C that provides easy-to-use implementations of fundamental data structures and a custom string type. It aims to reduce boilerplate and simplify development for C projects that require dynamic arrays, stacks, queues, or hash tables.

Key features include:
*   **String Manipulation**: A custom string type with functions to create, destroy, and query size/capacity.
*   **Data Structures**:
    *   Dynamic arrays (vectors)
    *   Stacks
    *   Queues
    *   Hash tables (hashmaps)

The project is structured as follows:
```
├── includes/         # Header files (.h)
├── src/              # Library implementation (.c)
├── tests/            # Unit tests
├── Makefile          # Build configuration
└── Dockerfile        # Docker environment configuration
```

## Tech Stack

*   [C](https://en.wikipedia.org/wiki/C_(programming_language))
*   [Make](https://www.gnu.org/software/make/)
*   [Check](https://libcheck.github.io/check/) (for unit testing)

## Usage

Below are the instructions for you to set up and use the library.

### Prerequisites

You need to have the following software installed:

*   A C compiler (e.g., [GCC](https://gcc.gnu.org/))
*   [Make](https://www.gnu.org/software/make/)
*   [Check](https://libcheck.github.io/check/) (for running tests)

### Installation and Setup

Follow the steps below:

1.  **Clone the repository**
    ```bash
    git clone https://github.com/luizvilasboas/easyc.git
    ```

2.  **Navigate to the project directory**
    ```bash
    cd easyc
    ```

3.  **Compile the library**
    ```bash
    make
    ```

4.  **(Optional) Install the library system-wide**
    ```bash
    sudo make install
    ```

### Workflow

To use the library in your own project, include the necessary headers and link against the `easyc` library during compilation.

1.  **Include headers in your C file:**
    ```c
    #include <easyc/base_string.h>
    #include <easyc/data_structures/vector.h>
    // ... and so on for other structures
    ```

2.  **Compile your program:**
    ```bash
    gcc -o my_program my_program.c -I/usr/local/include/easyc -L/usr/local/lib/easyc -leasyc
    ```
    For more detailed examples, please refer to the [docs](https://github.com/luizvilasboas/easyc/tree/main/docs).

### Testing

To run the library's unit tests, execute the following command:
```bash
make test
```

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
