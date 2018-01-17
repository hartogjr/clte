# @author    Simon de Hartog <simon@fs2a.pro>
# @copyright Fs2a Ltd. (c) 2018
# vim:set ts=2 sw=2 noexpandtab:

find_package (BISON)
find_package (FLEX)

BISON_TARGET (ClteParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET (ClteScanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY (ClteScanner ClteParser)

add_library (clte
	${BISON_ClteParser_OUTPUTS}
	${FLEX_ClteScanner_OUTPUTS}
)
