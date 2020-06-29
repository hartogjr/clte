/* BSD 3-Clause License
 *
 * Copyright (c) 2020, Simon de Hartog <simon@dehartog.name>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * vim:set ts=4 sw=4 noet: */

#pragma once

#include <istream>
#include <ostream>

namespace Clte
{

	/** Render a template from the input stream to the output stream, using
	 * data to fill it. */
	class Renderer
	{
		protected:
		// Input stream to use
		std::istream * in_a;

		// Output stream to use
		std::ostream * out_a;

		public:
		// Default constructor
		Renderer();

		// Default destructor
		~Renderer();

		/** Read the data to use from a file.
		 * @param filename_i Filename to read YAML data from.
		 * @returns True if successful, false if not. */
		bool data(const std::string & filename_i);

		/** Set the input stream to read the template from.
		 * @param in_i Pointer to input stream.
		 * @throws std::invalid_argument when @p in_i is NULL
		 * @throws std::logic_error when input stream is already set */
		void in(std::istream * in_i);

		/** Set the output stream to write to.
		 * @param out_i Pointer to output stream.
		 * @throws std::invalid_argument when @p out_i is NULL
		 * @throws std::logic_error when output stream is already set */
		void out(std::istream * out_i);

		/** Render the input template to the output. */
		void render();

	};

} // Clte namespace
