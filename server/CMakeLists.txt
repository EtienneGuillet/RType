file(
        GLOB_RECURSE
        RTYPE_SOURCES_SERVER
        sources/*.cpp
        sources/*.hpp
)

add_executable(r-type_server ${RTYPE_SOURCES_SERVER} ${RTYPE_SOURCES_COMMON})

target_include_directories(
        r-type_server PUBLIC
        ${PROJECT_SOURCE_DIR}/commons/sources
        sources
)
target_link_libraries(
        r-type_server
        ${CONAN_LIBS}
)

if (UNIX)
	target_link_libraries(
		r-type_server
		dl
	)
endif (UNIX)

add_subdirectory(tests)