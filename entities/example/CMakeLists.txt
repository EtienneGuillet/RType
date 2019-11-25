file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_EXAMPLE
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(example_entity SHARED ${RTYPE_SOURCES_ENTITY_EXAMPLE})

target_include_directories(
        example_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_custom_command(TARGET example_entity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:example_system> ${SERVER_ENTITIES_FOLDER}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:example_system> ${CLIENT_ENTITIES_FOLDER}
        )

add_subdirectory(tests)