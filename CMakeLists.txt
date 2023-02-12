cmake_minimum_required(VERSION 3.10)

project(folder_digger)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "Release")

add_definitions(-DFORMAT_SET)
add_definitions(-DFORMAT_MAP)
add_definitions(-DFORMAT_VECTOR)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)