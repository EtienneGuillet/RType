file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_TEXTBOX
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(textbox_entity SHARED ${RTYPE_SOURCES_ENTITY_TEXTBOX})

target_include_directories(
        textbox_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_custom_command(TARGET textbox_entity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:textbox_entity> ${CLIENT_ENTITIES_FOLDER}
        )

add_subdirectory(tests)
