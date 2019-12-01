file(
        GLOB_RECURSE
        RTYPE_SOURCES_OMEGATRON_SYSTEM_TESTS
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/systems/example/*.cpp
        ${PROJECT_SOURCE_DIR}/systems/example/*.hpp
        *.cpp
        *.hpp
)

add_executable(tests_omegatron_system ${RTYPE_SOURCES_OMEGATRON_SYSTEM_TESTS})

target_include_directories(
        tests_omegatron_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)
target_link_libraries(
        tests_omegatron_system
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME omegatron_system COMMAND tests_omegatron_system)
add_dependencies(${TESTS_RULE} tests_omegatron_system)