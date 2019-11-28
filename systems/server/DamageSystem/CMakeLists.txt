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

add_custom_command(TARGET damage_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:damage_system> ${SERVER_SYSTEMS_FOLDER}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:damage_system> ${CLIENT_SYSTEMS_FOLDER}
)