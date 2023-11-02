cmake_minimum_required(VERSION 3.5)  # CMake version check
project(Aurora)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")# Enable c++14 standard
set(source_dir "${PROJECT_SOURCE_DIR}/src")
# Add main.cpp file of the project root directory as a source file
file(GLOB source_files "${source_dir}/*.cpp")

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(Aurora src/main.cpp)
