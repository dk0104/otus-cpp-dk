cmake_minimum_required(VERSION 3.24)
include(../../CMake/DefaultCXX.cmake)

message(STATUS "Configuring template-lib")
message(STATUS "PATCH_VERSION: ${PATCH_VERSION}")
option(TEMPLATE_LIB_BUILD_VALID "Set valid if run atleast once" ON)
if(TEMPLATE_LIB_BUILD_VALID)
  message(STATUS "add counter for template-lib")
  set(VER_CNT "${PATCH_VERSION}")
  message(STATUS "VER_CNT: ${VER_CNT}")
endif()
configure_file(version.h.in version.h @ONLY)

file(
  GLOB_RECURSE SOURCE_FILES
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  CONFIGURE_DEPENDS ${SOURCE_FILES_FILTER})
message(STATUS "SOURCE_FILES: ${SOURCE_FILES}")

add_library(template-lib STATIC ${SOURCE_FILES})
add_library(tpl::Lib ALIAS template-lib)
target_compile_features(template-lib PUBLIC cxx_std_20)
target_compile_options(template-lib PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(template-lib PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(template-lib PUBLIC hpp)
