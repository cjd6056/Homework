cmake_minimum_required(VERSION 3.23)
project(AERSP424_HW2)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the Matplot++ directory
include_directories(
    "C:/Users/conor.CONORS-XPS-15/OneDrive/Desktop/Repos/Homework/HW_2/Include/matplotplusplus/source"
    "C:/Users/conor.CONORS-XPS-15/OneDrive/Desktop/Repos/Homework/HW_2/Include/matplotplusplus/source/matplot/detail"
)

# Add the executable and source files
add_executable(AERSP424_HW2 src/main.cpp src/main_hw2.cpp)
