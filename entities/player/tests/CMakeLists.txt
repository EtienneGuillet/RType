file(
        GLOB_RECURSE
        RTYPE_SOURCES_PLAYER_ENTITY_TESTS
        ${RTYPE_SOURCES_COMMON}
        ${PROJECT_SOURCE_DIR}/entities/example/*.cpp
        ${PROJECT_SOURCE_DIR}/entities/example/*.hpp
        *.cpp
        *.hpp
)

add_executable(tests_player_entity ${RTYPE_SOURCES_PLAYER_ENTITY_TESTS})

target_include_directories(
        tests_player_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/client/sources
        ${PROJECT_SOURCE_DIR}/client/tests
        ${PROJECT_SOURCE_DIR}/commons/tests
)
target_link_libraries(
        tests_player_entity
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME tests_player_entity COMMAND tests_example_entity)
add_dependencies(${TESTS_RULE} tests_player_entity)