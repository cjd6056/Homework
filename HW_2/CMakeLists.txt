cmake_minimum_required(VERSION 3.22) # Specify CMake version.
project(matplot++
    DESCRIPTION "424 Homework 2 MatPlot++ Integrated"
    VERSION 0.0.1) # A project name. This can be anything.
set(CMAKE_CXX_STANDARD 17) # Specify C++ version.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
add_compile_definitions(_USE_MATH_DEFINES)

# set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic -Wextra")
message(STATUS "CMakeLists.txt is at ${PROJECT_SOURCE_DIR}") # To print something.
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/matplotplusplus/install")
find_package(Matplot++ REQUIRED)
include(GNUInstallDirs)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Create a binary file. 
# The first argument is the name of the binary file.
# It can be anything. In this case, it is set to be the project name.
# The other arguments are source files.
# Header files are not needed in add_executable(), assuming they are properly included.
add_executable(${CMAKE_PROJECT_NAME} ${all_SRCS})

target_link_libraries(${CMAKE_PROJECT_NAME} Matplot++::matplot)
# target_link_libraries(${CMAKE_PROJECT_NAME} m)
