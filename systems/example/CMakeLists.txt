file(
        GLOB_RECURSE
        RTYPE_SOURCES_SYSTEM_EXAMPLE
        ${RTYPE_SOURCES_COMMON}
        *.cpp
)

add_library(example_system SHARED ${RTYPE_SOURCES_SYSTEM_EXAMPLE})

target_include_directories(
        example_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_subdirectory(tests)