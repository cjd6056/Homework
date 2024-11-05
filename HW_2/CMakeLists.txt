cmake_minimum_required(VERSION 3.23)
project(AERSP424_HW2)
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/matplotplusplus/install")
find_package(Matplot++ REQUIRED)
include(GNUInstallDirs)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the Matplot++ directory containing matplot.h
#include_directories(
#   "C:/Users/conor.CONORS-XPS-15/OneDrive/Desktop/Repos/Homework/HW_2/Include/matplotplusplus/source/matplot"
# )

# Add the executable and source files
add_executable(AERSP424_HW2 src/main.cpp src/main_hw2.cpp)
#target_link_libraries(AERSP424_HW2 INTERFACE Matplot++::matplot)
target_link_libraries(AERSP424_HW2 Matplot++::matplot)
