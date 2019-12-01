file(
        GLOB_RECURSE
        RTYPE_SOURCES_clean_entities_system_TESTS
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/systems/CleanEntitiesSystem/*.cpp
        ${PROJECT_SOURCE_DIR}/systems/CleanEntitiesSystem/*.hpp
        *.cpp
        *.hpp
)

add_executable(tests_clean_entities_system ${RTYPE_SOURCES_clean_entities_system_TESTS})

target_include_directories(
        tests_clean_entities_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/client/sources
        ${PROJECT_SOURCE_DIR}/client/tests
        ${PROJECT_SOURCE_DIR}/commons/tests
)
target_link_libraries(
        tests_clean_entities_system
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME clean_entities_system COMMAND tests_clean_entities_system)
add_dependencies(${TESTS_RULE} tests_clean_entities_system)