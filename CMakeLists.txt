cmake_minimum_required(VERSION 3.10)
project(lab2_octal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SRC_FILES src/*.cpp)

add_library(lab2 ${SRC_FILES})
target_include_directories(lab2 PUBLIC include)

add_executable(main main.cpp)
target_link_libraries(main lab2)

enable_testing()
file(GLOB TEST_FILES tests/*.cpp)

add_executable(tests ${TEST_FILES})

target_link_libraries(tests PRIVATE lab2 GTest::gtest_main)
target_include_directories(tests PRIVATE include)

include(GoogleTest)
gtest_discover_tests(tests)