file(
        GLOB_RECURSE
        RTYPE_SOURCES_SYSTEM_SFML
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(sfml_system SHARED ${RTYPE_SOURCES_SYSTEM_SFML})

target_link_libraries(
        sfml_system
        ${CONAN_LIBS}
)

target_include_directories(
        sfml_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_custom_command(TARGET sfml_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml_system> ${CLIENT_SYSTEMS_FOLDER}
        )

add_subdirectory(tests)