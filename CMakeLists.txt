cmake_minimum_required(VERSION 3.12)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
set(CMAKE_CXX_STANDARD 17)

project(Minus2CCompiler)

find_package(Boost 1.67.0 REQUIRED COMPONENTS system filesystem)

include (AddGTest)

enable_testing()

add_subdirectory(Parser)
add_subdirectory(Interpreter)
