file(
        GLOB_RECURSE
        RTYPE_SOURCES_clean_entities_system
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(clean_entities_system SHARED ${RTYPE_SOURCES_clean_entities_system})

target_include_directories(
        clean_entities_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_custom_command(TARGET clean_entities_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:clean_entities_system> ${SERVER_SYSTEMS_FOLDER}
)

add_subdirectory(tests)