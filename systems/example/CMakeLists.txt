file(
        GLOB_RECURSE
        RTYPE_SOURCES_SYSTEM_EXAMPLE
        *.cpp
)

add_library(example_system SHARED ${RTYPE_SOURCES_SYSTEM_EXAMPLE})

target_include_directories(
        example_system PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/commons/sources
)