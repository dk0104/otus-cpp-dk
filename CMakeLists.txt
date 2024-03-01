cmake_minimum_required(VERSION 3.24)
set(PATCH_VERSION
    "1"
    CACHE INTERNAL "Patch version")
message(STATUS "Patch version: ${PATCH_VERSION}")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
message(STATUS "Project version: ${PROJECT_VESRION}")
project(template VERSION ${PROJECT_VESRION})
include(CMake/DefaultCXX.cmake)

find_package(GTest)

set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
enable_testing()
add_subdirectory(src)
add_subdirectory(test)



