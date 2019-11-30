file(
        GLOB_RECURSE
        RTYPE_SOURCES_SPAWNABLE_ENTITY_TESTS
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/entities/spawnable/*.cpp
        ${PROJECT_SOURCE_DIR}/entities/spawnable/*.hpp
        *.cpp
        *.hpp
)

add_executable(tests_spawnable_entity ${RTYPE_SOURCES_SPAWNABLE_ENTITY_TESTS})

target_include_directories(
        tests_spawnable_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/client/sources
        ${PROJECT_SOURCE_DIR}/client/tests
        ${PROJECT_SOURCE_DIR}/commons/tests
)
target_link_libraries(
        tests_spawnable_entity
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME spawnable_entity COMMAND tests_spawnable_entity)
add_dependencies(${TESTS_RULE} tests_spawnable_entity)