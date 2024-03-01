cmake_minimum_required(VERSION 3.24)
project(temlpate_Test CXX)
include(GoogleTest)

if(NOT TARGET tpl::Lib)
  find_package(tpl::Lib CONFIG REQUIRED)
endif()

add_executable(${PROJECT_NAME} test_version_counter.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main tpl::Lib)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

gtest_discover_tests(${PROJECT_NAME} TEST_PREFIX "Test_")
