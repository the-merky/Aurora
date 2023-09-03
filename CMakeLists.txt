cmake_minimum_required(VERSION 3.13)  # CMake version check
project(Aurora)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14
VERSION
    1.0
  DESCRIPTION
    "A chess engine."
  LANGUAGES
    CXX            # Enable c++14 standard
 )
# Add main.cpp file of the project root directory as a source file


# Add executable target with source files listed in SOURCE_FILES variable
add_executable(/bin/main src/main.cpp)
