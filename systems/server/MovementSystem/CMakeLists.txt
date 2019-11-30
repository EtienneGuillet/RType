file(
        GLOB_RECURSE
        RTYPE_SOURCES_MOVEMENT_SYSTEM
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(movement_system SHARED ${RTYPE_SOURCES_MOVEMENT_SYSTEM})

target_include_directories(
        movement_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        sources/
)

add_custom_command(TARGET movement_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:movement_system> ${SERVER_SYSTEMS_FOLDER}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:movement_system> ${CLIENT_SYSTEMS_FOLDER}
)