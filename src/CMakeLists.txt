cmake_minimum_required(VERSION 3.24)


set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
if(NOT CMAKE_BUILD_TYPE) 
  set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(lib)
include(GNUInstallDirs)


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Debug>:-O0>")
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets)
