file(
        GLOB_RECURSE
        RTYPE_SOURCES_SYSTEM_CLIENT_GAME_NETWORK_ENTITY_SYNC
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(clientGameNetworkEntitySync_system SHARED ${RTYPE_SOURCES_SYSTEM_CLIENT_GAME_NETWORK_ENTITY_SYNC})

target_include_directories(
        clientGameNetworkEntitySync_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

target_link_libraries(
        clientGameNetworkEntitySync_system
        ${CONAN_LIBS}
)

add_custom_command(TARGET clientGameNetworkEntitySync_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:clientGameNetworkEntitySync_system> ${CLIENT_SYSTEMS_FOLDER}
        )