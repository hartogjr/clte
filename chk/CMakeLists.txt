# @author    Simon de Hartog <simon@fs2a.pro>
# @copyright Fs2a Ltd. (c) 2018
# vim:set ts=2 sw=2 noexpandtab:

find_package (CppUnit REQUIRED)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	INCLUDE (CodeCoverage)
	SETUP_TARGET_FOR_COVERAGE(chkcov chk coverage)
	add_custom_target (
		RunCoverage ALL
		DEPENDS chkcov
	)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

include_directories (
	${CPPUNIT_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/src
)

add_executable (chk
	chk.cpp
)

target_link_libraries (chk
	${CPPUNIT_LIBRARY}
	libclte
)

