project(R-Type)
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    add_definitions("-fPIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wuninitialized -Wunreachable-code")
endif (UNIX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

if (APPLE)
    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
endif (APPLE)

enable_testing()

file(
        GLOB_RECURSE
        RTYPE_SOURCES_COMMON
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
)

include_directories(SYSTEM ${CMAKE_INCLUDE_PATH})

add_subdirectory(server)
add_subdirectory(client)

file(GLOB BUILD_DEPENDENCY "build_dependency/*")
file(COPY ${BUILD_DEPENDENCY} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(systems)
add_subdirectory(entities)
add_subdirectory(commons)

add_custom_target(tests_run ctest --verbose)