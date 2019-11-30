file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_BYDOS_SLAVE
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(bydos_slave_entity SHARED ${RTYPE_SOURCES_ENTITY_BYDOS_SLAVE})

target_include_directories(
        bydos_slave_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_custom_command(TARGET bydos_slave_entity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:bydos_slave_entity> ${SERVER_ENTITIES_FOLDER}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:bydos_slave_entity> ${CLIENT_ENTITIES_FOLDER}
        )

add_subdirectory(tests)