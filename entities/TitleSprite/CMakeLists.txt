file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_TITLESPRITE
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(titleSprite_entity SHARED ${RTYPE_SOURCES_ENTITY_TITLESPRITE} sources/TitleSpriteEntity.cpp sources/TitleSpriteEntity.hpp sources/TitleSpriteEntityAPI.cpp sources/TitleSpriteEntityAPI.hpp sources/entryPoint.cpp)

target_include_directories(
        titleSprite_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_subdirectory(tests)
