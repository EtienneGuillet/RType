file(
        GLOB_RECURSE
        RTYPE_SOURCES_EXAMPLE_SYSTEM_TESTS
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/systems/example/*.cpp
        ${PROJECT_SOURCE_DIR}/systems/example/*.hpp
        *.cpp
        *.hpp
)

add_executable(tests_example_system ${RTYPE_SOURCES_EXAMPLE_SYSTEM_TESTS})

target_include_directories(
        tests_example_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/client/sources
        ${PROJECT_SOURCE_DIR}/client/tests
        ${PROJECT_SOURCE_DIR}/commons/tests
)
target_link_libraries(
        tests_example_system
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME example_system COMMAND tests_example_system)