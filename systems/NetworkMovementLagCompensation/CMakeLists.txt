file(
        GLOB_RECURSE
        RTYPE_SOURCES_SYSTEM_NETWORK_MOVEMENT_LAG_COMPENSATION
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(networkMovementLagCompensation_system SHARED ${RTYPE_SOURCES_SYSTEM_NETWORK_MOVEMENT_LAG_COMPENSATION})

target_include_directories(
        networkMovementLagCompensation_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

target_link_libraries(
        networkMovementLagCompensation_system
        ${CONAN_LIBS}
)

add_custom_command(TARGET networkMovementLagCompensation_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:networkMovementLagCompensation_system> ${CLIENT_SYSTEMS_FOLDER}
        )