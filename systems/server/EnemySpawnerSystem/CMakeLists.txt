file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENEMY_SPAWNER_SYSTEM
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(enemy_spawner_system SHARED ${RTYPE_SOURCES_ENEMY_SPAWNER_SYSTEM})

target_include_directories(
        enemy_spawner_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        sources/
)

add_custom_command(TARGET enemy_spawner_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:enemy_spawner_system> ${SERVER_SYSTEMS_FOLDER}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:enemy_spawner_system> ${SERVER_SYSTEMS_FOLDER}
)