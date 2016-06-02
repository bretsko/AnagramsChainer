cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
project(AnagramFinder)

enable_testing()

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(AnagramFinder)

include(cppcheck.cmake)

