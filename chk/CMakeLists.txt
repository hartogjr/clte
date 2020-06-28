# BSD 3-Clause License
#
# Copyright (c) 2020, Simon de Hartog <simon@dehartog.name>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# * Neither the name of the copyright holder nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# vim:set ts=4 sw=4 noet:

# Include stuff for code coverage
if (RUN_COVERAGE STREQUAL "ON")
	include(CodeCoverage)
	append_coverage_compiler_flags()
	setup_target_for_coverage_gcovr_html(
		NAME coverage
		EXECUTABLE chk
		BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src"
		EXCLUDE "${PROJECT_SOURCE_DIR}/chk"
	)
endif (RUN_COVERAGE STREQUAL "ON")

find_package (CppUnit REQUIRED)

include_directories (
	${CPPUNIT_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/src
)

add_executable (chk
	chk.cpp
)

target_link_libraries (chk
	${CPPUNIT_LIBRARY}
	clte
)
