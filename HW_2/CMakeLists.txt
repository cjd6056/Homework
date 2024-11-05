cmake_minimum_required(VERSION 3.23)
project(AERSP424_HW2)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for the project
include_directories(${CMAKE_SOURCE_DIR})
include_directories("C:/Users/conor.CONORS-XPS-15/Downloads/matplotplusplus-1.2.1/source/matplot")

# Add the executable and its source files
add_executable(AERSP424_HW2 src/main_hw2.cpp src/main.cpp)
