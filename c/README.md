# C sandbox

## CMake tips

```sh
# Setup
cmake -B build -S . -G Ninja

# Build
cmake --build build

# Test
ctest --test-dir build --output-junit xunit/results.xml
```
