cmake_minimum_required(VERSION 3.16)
project(lru-cache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SRC_ALL "src/*.cpp")
file(GLOB_RECURSE SRC_LIB "src/*.cpp")
list(FILTER SRC_LIB EXCLUDE REGEX ".*/main\.cpp$")

add_executable(lru-cache ${SRC_ALL})

enable_testing()
add_executable(unit_tests tests/test.cpp ${SRC_LIB})
add_test(NAME AllTests COMMAND unit_tests)
