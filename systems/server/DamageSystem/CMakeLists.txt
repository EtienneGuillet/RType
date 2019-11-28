file(
        GLOB_RECURSE
        RTYPE_SOURCES_DAMAGE_SYSTEM
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(damage_system SHARED ${RTYPE_SOURCES_DAMAGE_SYSTEM})

target_include_directories(
        damage_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        sources/
)