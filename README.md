# CSS501 Program1: MTF v Transpose

If you use your `driver.cpp` or `LLStats.cpp`, build with:

```bash
g++ -std=c++11 *.cpp
./a.out
```

## Unit tests
To run unit tests (in the tests subdir):
```bash
cmake -S. -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
cd build && ctest
```

## linter
Lots of warning if using clang-tidy, there is a step defined. Build with the command from tests first, then:

```bash
cd build && make clang-tidy-check
```

