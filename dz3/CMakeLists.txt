cmake_minimum_required(VERSION 3.19)
project(dz3)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/src/RK3.cpp")

add_executable(dz3 ${sources})
