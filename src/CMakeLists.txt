# @author    Simon de Hartog <simon@fs2a.pro>
# @copyright Fs2a Ltd. (c) 2018
# vim:set ts=2 sw=2 noexpandtab:

find_package (BISON)
find_package (FLEX)

# BISON_TARGET (ClteParser parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET (ClteScanner scanner.lpp ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
# ADD_FLEX_BISON_DEPENDENCY (ClteScanner ClteParser)

message (STATUS "Flex outs: ${FLEX_ClteScanner_OUTPUTS}")

add_library (libclte STATIC
	#	${BISON_ClteParser_OUTPUTS}
	${FLEX_ClteScanner_OUTPUTS}
)

add_executable (clte
	main.cpp
)

target_link_libraries (clte
	libclte
)
