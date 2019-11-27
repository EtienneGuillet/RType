file(
        GLOB_RECURSE
        RTYPE_SOURCES_SYSTEM_OMEGATRON
        ${RTYPE_SOURCES_COMMON}
        sources/*.cpp
)

add_library(omegatron_system SHARED ${RTYPE_SOURCES_SYSTEM_OMEGATRON} sources/OmegatronSystemAPI.cpp sources/OmegatronSystemAPI.hpp)

target_include_directories(
        omegatron_system PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
)

add_subdirectory(tests)