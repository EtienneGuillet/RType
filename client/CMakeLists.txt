file(
        GLOB_RECURSE
        RTYPE_SOURCES_CLIENT
        ${PROJECT_SOURCE_DIR}/client/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/client/sources/*.hpp
)

add_executable(r-type_client ${RTYPE_SOURCES_CLIENT} ${RTYPE_SOURCES_COMMON})

target_include_directories(
        r-type_client PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/commons/sources
        ${PROJECT_SOURCE_DIR}/client/sources
)

target_link_libraries(
        r-type_client
        ${CONAN_LIBS}
)
