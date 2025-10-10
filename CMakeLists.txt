cmake_minimum_required(VERSION 3.14)
project(cdlinkedlist)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cdll)
target_sources(cdll
   PRIVATE
      CDLinkedList.cpp
   PUBLIC
      CDLinkedList.h
)
target_include_directories(cdll
   PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
)

enable_testing()
add_subdirectory(tests)

