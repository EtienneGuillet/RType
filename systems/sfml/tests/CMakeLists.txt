file(
        GLOB_RECURSE
        RTYPE_SOURCES_SFML_SYSTEM_TESTS
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/systems/sfml/*.cpp
        ${PROJECT_SOURCE_DIR}/systems/sfml/*.hpp
)

add_executable(tests_sfml_system ${RTYPE_SOURCES_SFML_SYSTEM_TESTS})

target_include_directories(
        tests_sfml_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/systems/sfml/sources
        ${PROJECT_SOURCE_DIR}/systems/sfml/tests
)
target_link_libraries(
        tests_sfml_system
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME example_system COMMAND tests_esfml_system)
add_dependencies(${TESTS_RULE} tests_sfml_system)