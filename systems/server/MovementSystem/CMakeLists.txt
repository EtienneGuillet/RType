file(
        GLOB_RECURSE
        RTYPE_SOURCES_MOVEMENT_SYSTEM
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(movement_system SHARED ${RTYPE_SOURCES_MOVEMENT_SYSTEM})

target_include_directories(
        movement_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        sources/
)