project(R-Type)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    add_definitions("-fPIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wuninitialized -Wunreachable-code")
endif (UNIX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

if (APPLE)
    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
endif (APPLE)

file(
        GLOB_RECURSE
        RTYPE_SOURCES_CLIENT
        ${PROJECT_SOURCE_DIR}/client/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/client/sources/*.hpp
)

file(
        GLOB_RECURSE
        RTYPE_SOURCES_SERVER
        ${PROJECT_SOURCE_DIR}/server/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/server/sources/*.hpp
)

file(
        GLOB_RECURSE
        RTYPE_SOURCES_COMMON
        ${PROJECT_SOURCE_DIR}/commons/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/*.hpp
)

file(
        GLOB_RECURSE
        RTYPE_SOURCES_CLIENT_TESTS
        ${PROJECT_SOURCE_DIR}/client/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/client/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/commons/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/*.hpp
        ${PROJECT_SOURCE_DIR}/client/tests/*.cpp
        ${PROJECT_SOURCE_DIR}/client/tests/*.hpp
)
list(REMOVE_ITEM RTYPE_SOURCES_CLIENT_TESTS "${PROJECT_SOURCE_DIR}/client/sources/main.cpp")

file(
        GLOB_RECURSE
        RTYPE_SOURCES_SERVER_TESTS
        ${PROJECT_SOURCE_DIR}/server/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/server/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/commons/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/*.hpp
        ${PROJECT_SOURCE_DIR}/server/tests/*.cpp
        ${PROJECT_SOURCE_DIR}/server/tests/*.hpp
)
list(REMOVE_ITEM RTYPE_SOURCES_SERVER_TESTS "${PROJECT_SOURCE_DIR}/server/sources/main.cpp")

add_executable(r-type_client ${RTYPE_SOURCES_CLIENT} ${RTYPE_SOURCES_COMMON})
target_include_directories(
        r-type_client PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/commons
        ${PROJECT_SOURCE_DIR}/client/sources
)
target_link_libraries(
        r-type_client
        ${CONAN_LIBS}
)

add_executable(r-type_server ${RTYPE_SOURCES_SERVER} ${RTYPE_SOURCES_COMMON})
target_include_directories(
        r-type_server PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/commons
        ${PROJECT_SOURCE_DIR}/server/sources
)
target_link_libraries(
        r-type_server
        ${CONAN_LIBS}
)

add_executable(tests_client ${RTYPE_SOURCES_CLIENT_TESTS})
target_include_directories(
        tests_client PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/commons
        ${PROJECT_SOURCE_DIR}/client/sources
        ${PROJECT_SOURCE_DIR}/client/tests
)
target_link_libraries(
        tests_client
        criterion
        ${CONAN_LIBS}
)

add_executable(tests_server ${RTYPE_SOURCES_SERVER_TESTS})
target_include_directories(
        tests_server PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/commons
        ${PROJECT_SOURCE_DIR}/server/sources
        ${PROJECT_SOURCE_DIR}/server/tests
)
target_link_libraries(
        tests_server
        criterion
        ${CONAN_LIBS}
)

add_custom_target(tests_run COMMAND tests_client COMMAND tests_server)

file(GLOB BUILD_DEPENDENCY "build_dependency/*")

file(COPY ${BUILD_DEPENDENCY} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
