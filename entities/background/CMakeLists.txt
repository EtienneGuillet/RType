file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_BACKGROUND
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(background_entity SHARED ${RTYPE_SOURCES_ENTITY_BACKGROUND})

target_include_directories(
        background_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

target_link_libraries(
        background_entity
        ${CONAN_LIBS}
)

add_custom_command(TARGET background_entity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:background_entity> ${CLIENT_ENTITIES_FOLDER}
        )

add_subdirectory(tests)
