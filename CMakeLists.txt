cmake_minimum_required(VERSION 3.30)
project(Real48 CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
if (CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
      ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif ()

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(real48 real48.cpp)
target_compile_options(real48 PRIVATE -Werror)

option(WITH_TESTS OFF)
if (WITH_TESTS)
  enable_testing()

  # unit tests
  find_package(GTest REQUIRED)
  add_executable(unit-tests unit-tests.cpp real48.cpp)
  target_link_libraries(unit-tests PRIVATE GTest::gtest_main)
  include(GoogleTest)
  target_compile_options(unit-tests PRIVATE -fsanitize=address,undefined)
  target_link_options(unit-tests PRIVATE -fsanitize=address,undefined)
  gtest_discover_tests(unit-tests TEST_PREFIX "unit-test.")

  # fuzzing tests
  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_executable(fuzzing-test fuzzing-test.cpp real48.cpp)
    add_test(
      NAME fuzzing-test
      COMMAND ${CMAKE_CURRENT_BINARY_DIR}/fuzzing-test -max_total_time=60 -max_len=1048576
    )
    target_compile_options(fuzzing-test PRIVATE -fsanitize=address,undefined,fuzzer)
    target_link_options(fuzzing-test PRIVATE -fsanitize=address,undefined,fuzzer)
  else ()
    message(WARNING "Current C/C++ compiler is not Clang, won't compile fuzzing test")
  endif()
endif ()
