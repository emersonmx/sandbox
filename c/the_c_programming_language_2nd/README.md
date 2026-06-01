# Codes from book "The programming language C - 2nd edition"

The requirements are:

- CMake 3.11 or better; 3.14+ highly recommended.
- A C17 compatible compiler

To configure:

```bash
cmake -S . -B build
```

Add `-GNinja` if you have Ninja.

To build:

```bash
cmake --build build
```
