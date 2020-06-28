/* Copyright (c) 2020 Simon de Hartog <simon@dehartog.name>

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its
contributors may be used to endorse or promote products derived from this
software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

vim:set ts=4 sw=4 noexpandtab: */

#pragma once

#include <stdlib.h>
#include <memory>
#include "commondefs.h"

namespace Fs2a {

	/** Fs2a Singleton class.
	 * If you want to use this class to model your own Singleton class, e.g.
	 * MySingleton, be sure to:
	 * 1. Use your class as template instantion of this one, so:
	 *    Fs2a::Singleton<MySingleton>
	 * 2. Use this as a superclass, so:
	 *    class MySingleton :public Fs2a::Singleton<MySingleton>
	 * 3. Declare this class a friend of your class, so add this line to your
	 *    class definition:
	 *    friend class Fs2a::Singleton<MySingleton>;
	 * 4. Follow the default conventions of declaring private constructors and
	 *    destructor.
	 * Summarizing, here's an example header definition for your Singleton
	 * class named MySingleton:
	 *
	 * class MySingleton : public Fs2a::Singleton<MySingleton>
	 * {
	 *   // Singleton template as friend for construction
	 *   friend class Fs2a::Singleton<MySingleton>;
	 *
	 *   private:
	 *   // Default constructor
	 *   MySingleton();
	 *
	 *   // Copy constructor
	 *   MySingleton(const MySingleton & obj_i) = delete;
	 *
	 *   // Assignment constructor
	 *   MySingleton & operator=(const MySingleton & obj_i) = delete;
	 *
	 *   // Destructor
	 *   ~MySingleton();
	 *
	 *   public:
	 *   ...
	 * };
	 */
	template <class T>
	class Singleton {
		private:
			/// Internal pointer to instance
			static T *instance_a;

			/// Mutex to prevent race conditions concerning instance_a
			static std::mutex mux_a;

			/// Copy constructor
			Singleton<T>(const Singleton<T> & obj_i) = delete;

			/// Assignment constructor
			Singleton<T> & operator=(const Singleton<T> & obj_i) = delete;

		protected:
			/** @{ Protected NoOp constructor and destructor to allow
			 * calling superclass ctor/dtor from subclasses. */
			inline Singleton() {}
			virtual inline ~Singleton() {}
			/** @} */

		public:
			/** Get the Singleton instance pointer.
			 * @returns a pointer to the singleton instance. */
			static inline T *instance()
			{
				GRD(mux_a);

				if (instance_a == nullptr) {
					instance_a = new T();
					atexit(Singleton<T>::close);
				}

				return instance_a;
			}

			/** Explicitly close the singleton */
			static inline void close()
			{
				GRD(mux_a);

				if (instance_a != nullptr) {
					delete instance_a;
					instance_a = nullptr;
				}
			}

			static inline bool is_constructed()
			{
				GRD(mux_a);

				return instance_a != nullptr;
			}

	};

	template <class T> T *Singleton<T>::instance_a = nullptr;
	template <class T> std::mutex Singleton<T>::mux_a;

} // Fs2a namespace
