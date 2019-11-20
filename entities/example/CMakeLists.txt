file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_EXAMPLE
        ${RTYPE_SOURCES_COMMON}
        *.cpp
)

add_library(example_entity SHARED ${RTYPE_SOURCES_ENTITY_EXAMPLE})

target_include_directories(
        example_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_subdirectory(tests)