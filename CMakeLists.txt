cmake_minimum_required(VERSION 3.12)

project(euler NONE)

enable_language(CXX)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)
add_subdirectory(euler)
