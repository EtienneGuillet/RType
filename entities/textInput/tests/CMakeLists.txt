file(
        GLOB_RECURSE
        RTYPE_SOURCES_TEXTINPUT_ENTITY_TESTS
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/entities/example/*.cpp
        ${PROJECT_SOURCE_DIR}/entities/example/*.hpp
        *.cpp
        *.hpp
)

add_executable(tests_textInput_entity ${RTYPE_SOURCES_TEXTINPUT_ENTITY_TESTS})

target_include_directories(
        tests_textInput_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/client/sources
        ${PROJECT_SOURCE_DIR}/client/tests
        ${PROJECT_SOURCE_DIR}/commons/tests
)
target_link_libraries(
        tests_textInput_entity
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME tests_textInput_entity COMMAND tests_textInput_entity)
add_dependencies(${TESTS_RULE} tests_textInput_entity)
