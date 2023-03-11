cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
project(baekjoon-solution)

set(PROBLEM_ID 1671)

set(MAIN_SOURCE
  ./${PROBLEM_ID}/main.cpp
)

add_executable(baekjoon-solution
  ${MAIN_SOURCE}
)
target_compile_options(baekjoon-solution BEFORE PRIVATE -fpermissive -pedantic)

set(CMAKE_CXX_STANDARD 20)
project(baekjoon-solution-test)

## GTEST
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

set(TEST_SOURCE
  ./test/test.cpp
  ./${PROBLEM_ID}/test.cpp
)


add_executable(baekjoon-solution-test
${MAIN_SOURCE}
${TEST_SOURCE}
)
target_compile_options(baekjoon-solution-test BEFORE PRIVATE -fpermissive -pedantic)
target_compile_definitions(baekjoon-solution-test PRIVATE TEST_ENABLED)
target_link_libraries(baekjoon-solution-test
  gtest_main
)

enable_testing()