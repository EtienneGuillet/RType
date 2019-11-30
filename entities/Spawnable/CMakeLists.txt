file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_SPAWNABLE
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(spawnable_entity SHARED ${RTYPE_SOURCES_ENTITY_SPAWNABLE})

target_include_directories(
        spawnable_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_custom_command(TARGET spawnable_entity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:spawnable_entity> ${SERVER_ENTITIES_FOLDER}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:spawnable_entity> ${CLIENT_ENTITIES_FOLDER}
        )

add_subdirectory(tests)