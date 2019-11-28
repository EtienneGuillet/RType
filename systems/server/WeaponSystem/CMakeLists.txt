file(
        GLOB_RECURSE
        RTYPE_SOURCES_WEAPON_SYSTEM
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(weapon_system SHARED ${RTYPE_SOURCES_WEAPON_SYSTEM})

target_include_directories(
        weapon_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        sources/
)