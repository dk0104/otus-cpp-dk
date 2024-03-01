cmake_minimum_required(VERSION 3.24)
project(template_bin)


set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
if(NOT CMAKE_BUILD_TYPE) 
  set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(lib)
include(GNUInstallDirs)


add_executable(template main.cpp)
target_link_libraries(template PRIVATE template-lib)
target_compile_features(template INTERFACE cxx_std_20)
target_compile_options(template PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(template PRIVATE "$<$<CONFIG:Debug>:-O0>")
install(TARGETS template EXPORT template-targets)

