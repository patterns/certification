# CSS501 Program2: Sorted List

If you use your `driver.cpp` , build with:

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

## Linter
Lots of warning if using clang-tidy, there is a step defined. Build with the command from tests first, then:
```bash
cd build && make clang-tidy-check
```

## Memory leaks
Look for memory leaks:
```bash
g++ -std=c++11 -g driver.cpp -o sortdebug
valgrind --leak-check=full ./sortdebug
```

