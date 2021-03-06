project(R-Type)
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

set(TESTS_RULE tests_run)

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

add_custom_target(${TESTS_RULE} ctest --verbose)

set(SERVER_ENTITIES_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/server/entities)
set(SERVER_SYSTEMS_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/server/systems)
set(CLIENT_ENTITIES_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/client/entities)
set(CLIENT_SYSTEMS_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/client/systems)

add_subdirectory(server)
add_subdirectory(client)

file(GLOB BUILD_DEPENDENCY "build_dependency/*")
file(COPY ${BUILD_DEPENDENCY} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(systems)
add_subdirectory(entities)
add_subdirectory(commons)