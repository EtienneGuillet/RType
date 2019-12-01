file(
        GLOB_RECURSE
        RTYPE_SOURCES_ENTITY_LOBBYCONTAINER
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(LobbyContainer_entity SHARED ${RTYPE_SOURCES_ENTITY_LOBBYCONTAINER} ../textInput/sources/TextInputEntity.cpp ../LobbyContainer/sources/LobbyContainerEntity.hpp)

target_include_directories(
        LobbyContainer_entity PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

target_link_libraries(
        LobbyContainer_entity
        ${CONAN_LIBS}
)

add_custom_command(TARGET LobbyContainer_entity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:LobbyContainer_entity> ${CLIENT_ENTITIES_FOLDER}
        )

add_subdirectory(tests)
