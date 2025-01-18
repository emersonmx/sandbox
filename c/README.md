# C sandbox

## CMake tips

```sh
# Setup
cmake -B build -S . -G Ninja

# Build
cmake --build build

# Test
ctest --test-dir build --output-junit build/xunit/results.xml

# Install
DESTDIR=staging cmake --install build --componente libmylib-dev
```
