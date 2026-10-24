# Build and Run Guide

### Quick Build & Test (Using Included Scripts)
```bash
./scripts/build-all.sh
./scripts/test-all.sh
```

### CMake Build
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
ctest --test-dir build --output-on-failure
```

### Build with Clang AddressSanitizer (Memory Leak & UB Check)
```bash
cmake -B build -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined"
cmake --build build
ctest --test-dir build
```
