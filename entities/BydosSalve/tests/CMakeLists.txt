file(
        GLOB_RECURSE
        RTYPE_SOURCES_BYDOS_SLAVE_ENTITY_TESTS
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/entities/BydosSalve/*.cpp
        ${PROJECT_SOURCE_DIR}/entities/BydosSalve/*.hpp
        *.cpp
        *.hpp
)

add_executable(tests_bydos_slave_entity ${RTYPE_SOURCES_BYDOS_SLAVE_ENTITY_TESTS})

target_include_directories(
        tests_bydos_slave_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/client/sources
        ${PROJECT_SOURCE_DIR}/client/tests
        ${PROJECT_SOURCE_DIR}/commons/tests
)
target_link_libraries(
        tests_bydos_slave_entity
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME bydos_slave_entity COMMAND tests_bydos_slave_entity)
add_dependencies(${TESTS_RULE} tests_bydos_slave_entity)