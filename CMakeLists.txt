cmake_minimum_required(VERSION 3.14)
project(cdlinkedlist)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cdll)
target_sources(cdll
   PRIVATE
      CDLinkedList.cpp
      mtflist.cpp
   PUBLIC
      CDLinkedList.h
      mtflist.h
)
target_include_directories(cdll
   PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
)

enable_testing()
add_subdirectory(tests)

# enable 'make clang-tidy-check'
set(sources ${CMAKE_SOURCE_DIR}/CDLinkedList.cpp ${CMAKE_SOURCE_DIR}/CDLinkedList.h)
add_custom_target(clang-tidy-check clang-tidy -p ${CMAKE_BINARY_DIR}/compile_commands.json -checks=cert* ${sources} DEPENDS ${sources})
add_custom_target(check DEPENDS clang-tidy-check)

