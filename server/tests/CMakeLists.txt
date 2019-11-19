file(
        GLOB_RECURSE
        RTYPE_SOURCES_SERVER_TESTS
        ${PROJECT_SOURCE_DIR}/server/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/server/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/commons/tests/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/tests/*.hpp
        *.cpp
        *.hpp
)

list(REMOVE_ITEM RTYPE_SOURCES_SERVER_TESTS "${PROJECT_SOURCE_DIR}/server/sources/main.cpp")

add_executable(tests_server ${RTYPE_SOURCES_SERVER_TESTS})

target_include_directories(
        tests_server PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/server/sources
        ${PROJECT_SOURCE_DIR}/server/tests
        ${PROJECT_SOURCE_DIR}/commons/tests
)

target_link_libraries(
        tests_server
        criterion
        ${CONAN_LIBS}
)
