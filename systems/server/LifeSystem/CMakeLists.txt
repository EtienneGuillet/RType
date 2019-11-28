file(
        GLOB_RECURSE
        RTYPE_SOURCES_LIFE_SYSTEM
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(life_system SHARED ${RTYPE_SOURCES_LIFE_SYSTEM})

target_include_directories(
        life_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        sources/
)