file(
        GLOB_RECURSE
        RTYPE_SOURCES_CLIENT
        sources/*.cpp
        sources/*.hpp
)

add_executable(r-type_client ${RTYPE_SOURCES_CLIENT} ${RTYPE_SOURCES_COMMON})

target_include_directories(
        r-type_client PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/commons/sources
        sources
)

target_link_libraries(
        r-type_client
        dl
        ${CONAN_LIBS}
)

add_subdirectory(tests)