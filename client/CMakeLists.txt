file(
        GLOB_RECURSE
        RTYPE_SOURCES_CLIENT
        sources/*.cpp
        sources/*.hpp
)

add_executable(r-type_client ${RTYPE_SOURCES_CLIENT} ${RTYPE_SOURCES_COMMON})

target_include_directories(
        r-type_client PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        sources
)

target_link_libraries(
        r-type_client
        ${CONAN_LIBS}
)

if (UNIX)
	target_link_libraries(
		r-type_client
		dl
	)
endif (UNIX)

file(MAKE_DIRECTORY ${CLIENT_ENTITIES_FOLDER})
file(MAKE_DIRECTORY ${CLIENT_SYSTEMS_FOLDER})

add_subdirectory(tests)