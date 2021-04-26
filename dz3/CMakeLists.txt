cmake_minimum_required(VERSION 3.19)
project(dz3)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")

file(GLOB sources
#        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/ArcGraph.cpp"
        "${PROJECT_SOURCE_DIR}/src/HashTable.h"
        "${PROJECT_SOURCE_DIR}/src/HashTable.cpp"
        "${PROJECT_SOURCE_DIR}/src/ListGraph.cpp"
        "${PROJECT_SOURCE_DIR}/src/MatrixGraph.cpp"
        "${PROJECT_SOURCE_DIR}/src/main.cpp")

add_executable(dz3 ${sources})
