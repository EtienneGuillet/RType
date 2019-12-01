file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_TEXTINPUT
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(textInput_entity SHARED ${RTYPE_SOURCES_ENTITY_TEXTINPUT})

target_include_directories(
        textInput_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

target_link_libraries(
        textInput_entity
        ${CONAN_LIBS}
)

add_custom_command(TARGET textInput_entity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:textInput_entity> ${CLIENT_ENTITIES_FOLDER}
        )

add_subdirectory(tests)
