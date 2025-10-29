






include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(search_test
  superclass_test.cc
  index_test.cc
  string_test.cc
  uint_test.cc
  charstar_test.cc
)
include_directories (search_test ..)
target_link_libraries(search_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(search_test)
