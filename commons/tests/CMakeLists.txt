file(
        GLOB_RECURSE
        RTYPE_SOURCES_COMMON_TESTS
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        *.cpp
        *.hpp
)

add_executable(tests_common ${RTYPE_SOURCES_COMMON_TESTS} ../sources/exception/GameStateException.hpp)

target_include_directories(
        tests_common PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/commons/tests
)
target_link_libraries(
        tests_common
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME common COMMAND tests_common)
add_dependencies(${TESTS_RULE} tests_common)