cmake_minimum_required(VERSION 3.22) # Specify CMake version.
project(homework02
    DESCRIPTION "AERSP_424_HW_2"
    VERSION 0.0.1) # A project name. This can be anything.
set(CMAKE_CXX_STANDARD 17) # Specify C++ version.
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic -Wextra")
message(STATUS "CMakeLists.txt is at ${PROJECT_SOURCE_DIR}") # To print something.
include(CTest)
enable_testing()

# Dependencies
find_package(OpenGL REQUIRED)

list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/glew/install")
find_package(GLEW REQUIRED)

list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/glfw/install")
find_package(glfw3 REQUIRED)

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
add_executable(${AERSP_424_HW_2} ${all_SRCS})

target_link_libraries(${AERSP_424_HW_2} m)
target_link_libraries(${AERSP_424_HW_2} OpenGL::GL glfw libglew_static Matplot++::matplot)

# Enable packaging
set(CMAKE_INSTALL_PREFIX .)
install(FILES ${all_SRCS} DESTINATION .
    PERMISSIONS OWNER_READ OWNER_WRITE WORLD_READ WORLD_EXECUTE COMPONENT deb
)

set(CPACK_PROJECT_NAME ${AERSP_424_HW_2})
set(CPACK_PROJECT_VERSION ${CMAKE_PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_SOURCE_IGNORE_FILES
    /.git
    /dist
    /results
    /.*build.*
    /\\\\.DS_Store
)
set(CPACK_ARCHIVE_COMPONENT_INSTALL 1)
include(CPack)
