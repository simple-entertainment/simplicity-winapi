cmake_minimum_required(VERSION 2.8)

include(../../simplicity/simplicity/simplicity-common.cmake)

# Project
project(simplicity-winapi)

# Paths
file(GLOB_RECURSE SRC_FILES src/main/c++/*.cpp src/main/c++/*.h)
include_directories(../../simplicity/simplicity/src/main/c++)
include_directories(src/main/c++)

# Output
add_library(simplicity-winapi STATIC ${SRC_FILES})

