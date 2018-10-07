cmake_minimum_required(VERSION 3.12)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
set(CMAKE_CXX_STANDARD 17)

project(--CCompiler)

find_package(BOOST REQUIRED)

include (AddGTest)

enable_testing()

add_subdirectory(Parser)
