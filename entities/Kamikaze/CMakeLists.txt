file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_KAMIKAZE
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(kamikaze_entity SHARED ${RTYPE_SOURCES_ENTITY_KAMIKAZE})

target_include_directories(
        kamikaze_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_custom_command(TARGET kamikaze_entity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:kamikaze_entity> ${SERVER_ENTITIES_FOLDER}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:kamikaze_entity> ${CLIENT_ENTITIES_FOLDER}
        )

add_subdirectory(tests)