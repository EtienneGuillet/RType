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

add_custom_command(TARGET weapon_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:weapon_system> ${SERVER_SYSTEMS_FOLDER}
)
