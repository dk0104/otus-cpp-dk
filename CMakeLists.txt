cmake_minimum_required(VERSION 3.24)
set(PATCH_VERSION
    "1"
    CACHE INTERNAL "!!! Patch version !!! ")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(print_ip VERSION ${PROJECT_VESRION} LANGUAGES CXX)
include(CMake/DefaultCXX.cmake)

set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
enable_testing()
add_subdirectory(src)
add_subdirectory(test)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT densi.keksel@keksel.biz)
include(CPack)
