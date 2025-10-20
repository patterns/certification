cmake_minimum_required(VERSION 3.14)
project(cdlinkedlist)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

####add_library(cdll)
####target_sources(cdll
####   PRIVATE
      ####SortedList.cpp

####   PUBLIC
####      SortedList.h
####)
####target_include_directories(cdll
####   PUBLIC
####      ${CMAKE_CURRENT_LIST_DIR}
####)

enable_testing()
add_subdirectory(tests)

# enable 'make clang-tidy-check'
set(SRC_LIST
   ${CMAKE_SOURCE_DIR}/SortedList.cpp
   ${CMAKE_SOURCE_DIR}/SortedList.h


)
add_custom_target(clang-tidy-check clang-tidy -p ${CMAKE_BINARY_DIR}/compile_commands.json -checks=cert* ${SRC_LIST} DEPENDS ${SRC_LIST})
add_custom_target(check DEPENDS clang-tidy-check)

