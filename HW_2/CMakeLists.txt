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

# This code is from here: https://github.com/alandefreitas/matplotplusplus/commit/1cb600f244a827e1d2760a7d66b01d6b00331f43#diff-e35b0e226d4a31f175b28cce8958c1e75175a89f521475f047d8d5723861af05R104

include(GenerateExportHeader)
generate_export_header(matplot
        BASE_NAME matplot
        EXPORT_MACRO_NAME MATPLOT_EXPORTS
        EXPORT_FILE_NAME matplot/detail/exports.h
        STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)
        target_include_directories(matplot
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/matplot/detail/exports.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/matplot/detail)

# Add the executable and source files
add_executable(AERSP424_HW2 src/main.cpp)
#target_link_libraries(AERSP424_HW2 INTERFACE Matplot++::matplot)
target_link_libraries(AERSP424_HW2 PUBLIC Matplot++::matplot)