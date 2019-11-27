file(
        GLOB_RECURSE
        RTYPE_SOURCES_SERVER_TESTS
        ${PROJECT_SOURCE_DIR}/server/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/server/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/server/tests/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/server/tests/sources/*.hpp
)

list(REMOVE_ITEM RTYPE_SOURCES_SERVER_TESTS "${PROJECT_SOURCE_DIR}/server/sources/main.cpp")

add_executable(tests_server ${RTYPE_SOURCES_SERVER_TESTS})

target_include_directories(
        tests_server PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/server/sources
        ${PROJECT_SOURCE_DIR}/server/tests/sources
        ${PROJECT_SOURCE_DIR}/commons/tests
)

target_link_libraries(
        tests_server
        criterion
        dl
        gcov
        ${CONAN_LIBS}
)

add_test(NAME server COMMAND tests_server)
add_dependencies(${TESTS_RULE} tests_server)

file(
        GLOB_RECURSE
        RTYPE_SOURCES_SERVER_FUNCTIONAL_TESTS
        ${PROJECT_SOURCE_DIR}/commons/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/sources/*.hpp
        ${PROJECT_SOURCE_DIR}/server/tests/functional/*.cpp
        ${PROJECT_SOURCE_DIR}/server/tests/functional/*.hpp
)

add_executable(tests_server_functional ${RTYPE_SOURCES_SERVER_FUNCTIONAL_TESTS})

target_include_directories(
        tests_server_functional PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/server/tests/functional
)

target_link_libraries(
        tests_server_functional
        ${CONAN_LIBS}
)

if (UNIX)
	target_link_libraries(
		r-tests_server_functional
		dl
	)
endif (UNIX)