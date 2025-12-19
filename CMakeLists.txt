cmake_minimum_required(VERSION 3.14)
project(lab_2)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Create the library from your implementation
add_library(ThirteenArray src/thirteen_array.cpp)

# Include current directory for header file
target_include_directories(ThirteenArray PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Download GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(tests 
tests/tests.cpp)
target_link_libraries(tests ThirteenArray GTest::gtest_main)

add_executable(main
src/main.cpp)
target_link_libraries(main
ThirteenArray)

# Register tests
include(GoogleTest)
gtest_discover_tests(tests)