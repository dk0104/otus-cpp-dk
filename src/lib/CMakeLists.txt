cmake_minimum_required(VERSION 3.24)
include(../../CMake/DefaultCXX.cmake)

file(
  GLOB_RECURSE SOURCE_FILES
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  CONFIGURE_DEPENDS ${SOURCE_FILES_FILTER})
  message(STATUS "progect name : ${PROJECT_NAME}")

add_library(${PROJECT_NAME}-lib STATIC ${SOURCE_FILES})
add_library(${PROJECT_NAME}::Lib ALIAS ${PROJECT_NAME}-lib)
target_compile_features(${PROJECT_NAME}-lib PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME}-lib PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(${PROJECT_NAME}-lib PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME}-lib PUBLIC hpp)
