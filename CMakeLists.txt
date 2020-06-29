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

cmake_minimum_required (VERSION 3.1)
if(POLICY CMP0015)
	cmake_policy(SET CMP0015 NEW)
endif()
if(POLICY CMP0056)
	cmake_policy(SET CMP0056 NEW)
endif()

project (clte CXX C)

# Set the Git repository root directory
execute_process (
	COMMAND git rev-parse --show-toplevel
	OUTPUT_VARIABLE REPOROOT
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Custom C/C++ flags
set (CUSTOM_FLAGS   "-Wall -Werror -Wextra -Wno-varargs -DREPOROOT='${REPOROOT}'")
set (CUSTOM_DEBUG   "-O0 -g3 -ggdb")
set (CUSTOM_RELEASE "-O3")

# Common linker flags
set (CMAKE_EXE_LINKER_FLAGS_DEBUG   "${CMAKE_EXE_LINKER_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} -s")

# Plain C flags
set (CMAKE_C_FLAGS         "${CUSTOM_FLAGS}")
set (CMAKE_C_FLAGS_DEBUG   "${CUSTOM_FLAGS} ${CUSTOM_DEBUG}")
set (CMAKE_C_FLAGS_RELEASE "${CUSTOM_FLAGS} ${CUSTOM_RELEASE}")

# C++ flags, mostly the same as C. CFLAGS are already included here.
set (CMAKE_CXX_FLAGS         "-std=gnu++17")
set (CMAKE_CXX_FLAGS_DEBUG   "${CUSTOM_FLAGS} ${CUSTOM_DEBUG}")
set (CMAKE_CXX_FLAGS_RELEASE "${CUSTOM_FLAGS} ${CUSTOM_RELEASE}")

# Find necessary packages
find_package (Boost REQUIRED COMPONENTS program_options)
find_package (FLEX)

add_subdirectory (src)
add_subdirectory (chk)
