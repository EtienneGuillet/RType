file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_MUSIC
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(Music_entity SHARED ${RTYPE_SOURCES_ENTITY_MUSIC} ../textInput/sources/TextInputEntity.cpp ../Music/sources/MusicEntity.hpp)

target_include_directories(
        Music_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

target_link_libraries(
        Music_entity
        ${CONAN_LIBS}
)

add_custom_command(TARGET Music_entity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Music_entity> ${CLIENT_ENTITIES_FOLDER}
        )

add_subdirectory(tests)
