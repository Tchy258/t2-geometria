cmake_minimum_required(VERSION 3.10.0)

project(Tarea2 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CTest)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(--coverage -g -O0)
endif()
add_subdirectory(src)
add_subdirectory(test)
