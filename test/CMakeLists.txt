cmake_minimum_required(VERSION 3.24)
project(temlpate_Test CXX)
include(GoogleTest)
include(../CMake/DefaultCXX.cmake)

if(NOT TARGET tpl::Lib)
  find_package(tpl::Lib CONFIG REQUIRED)
endif()

file(
  GLOB_RECURSE SOURCE_FILES
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  CONFIGURE_DEPENDS ${SOURCE_FILES_FILTER})
message(STATUS "Test SOURCE_FILES: ${SOURCE_FILES}")

set(TEST_RESOURCE_FILES ip_filter.tsv)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TEST_RESOURCE_FILES}
  COMMAND ${CMAKE_COMMAND} -E copy
       ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_RESOURCE_FILES}
       ${CMAKE_CURRENT_BINARY_DIR}/${TEST_RESOURCE_FILES}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_RESOURCE_FILES}
)

add_executable(${PROJECT_NAME}
  ${CMAKE_CURRENT_BINARY_DIR}/${TEST_RESOURCE_FILES}
  ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main tpl::Lib)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

gtest_discover_tests(${PROJECT_NAME} TEST_PREFIX "Test_")
