# CSS501 Program2: Sorted List
## About
SortedList is a double linked list of SListNodes.
 The list head is tagged with the ntype of `HeadNode`, and is linked to the first node AND the last node.
 Other list nodes that contain data are tagged as ntype of `ItemNode`.

1. Sort order is maintained at the time of insert.
2. Insert is done by looping through list nodes checking for the item with greater/equal value.
3. Node items can be fundamental types and specified as template type parameters.
4. The std::string data type is supported besides fundamental types.


## Quickstart
If you use your `driver3.cpp` , build with:

```bash
g++ -std=c++11 driver3.cpp
./a.out
```


## Caveats
1. The sort order for data type std::string is not the expected outcome for numbers.
   For example, "22" is lower in value than "5" when compared as strings.
2. Google Test shows SEGFAULT for the std::string template type parameter
   - Irrespective of C++11 or C++17 setting for CMAKE_CXX_STANDARD
   - Related to destructor ~SortedList which invokes clear() (and delete)
   - Build (using g++ -std=c++11) is error-free
3. The remove method is a simple loop. I realized that with a ordered list it is possible to use binary search but ran out of time

## References
Move ctor/assignment
 by [MS](https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170)

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

