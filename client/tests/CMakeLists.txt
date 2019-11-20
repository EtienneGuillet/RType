file(
        GLOB_RECURSE
        RTYPE_SOURCES_CLIENT_TESTS
        ${PROJECT_SOURCE_DIR}/client/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/client/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        *.cpp
        *.hpp
)

list(REMOVE_ITEM RTYPE_SOURCES_CLIENT_TESTS "${PROJECT_SOURCE_DIR}/client/sources/main.cpp")

add_executable(tests_client ${RTYPE_SOURCES_CLIENT_TESTS})

target_include_directories(
        tests_client PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/client/sources
        ${PROJECT_SOURCE_DIR}/client/tests
        ${PROJECT_SOURCE_DIR}/commons/tests
)
target_link_libraries(
        tests_client
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME client COMMAND tests_client)