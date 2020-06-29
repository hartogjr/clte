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

#include <stdexcept>
#include "Logger.h"
#include "Renderer.h"

namespace Clte
{
	Renderer::Renderer()
	: in_a(nullptr), out_a(nullptr)
	{ }

	Renderer::~Renderer()
	{ }

	void Renderer::in(std::istream * in_i)
	{
		LCET(in_i != nullptr, std::invalid_argument, "Pointer to input stream may not be NULL");
		LCET(in_a == nullptr, std::logic_error, "Input stream is already set");
		in_a = in_i;
	}

	void Renderer::out(std::ostream * out_i)
	{
		LCET(out_i != nullptr, std::invalid_argument, "Pointer to output stream may not be NULL");
		LCET(out_a == nullptr, std::logic_error, "Output stream is already set");
		out_a = out_i;
	}

	void Renderer::render()
	{
		LCET(in_a != nullptr, std::logic_error, "Input stream pointer wasn't set, call in() first.");
		LCET(out_a != nullptr, std::logic_error, "Output stream pointer wasn't set, call out() first.");
	}

} // Clte namespace
