/** @author   Simon de Hartog <simon@fs2a.pro>
 * @copyright Fs2a Ltd. (c) 2017 */

#pragma once

#include <memory>
#include <mutex>

namespace Fs2a {

	template <class T>
	class Singleton {
		private:
			/// Internal pointer to instance
			static T *instance_a;

			/// Mutex to prevent race conditions upon construction
			static std::mutex mux_a;

		protected:
			/// Default constructor
			inline Singleton<T>() {}

			/// Copy constructor
			Singleton<T>(const Singleton<T> & obj_i) = delete;

			/// Assignment constructor
			Singleton<T> & operator=(const Singleton<T> & obj_i) = delete;

			/// Destructor
			inline ~Singleton<T>() {}

		public:
			/** Get the Singleton instance pointer.
			 * @returns a pointer to the singleton instance. */
			static inline T *instance()
			{
				std::lock_guard<std::mutex> lck(mux_a);

				if (instance_a == nullptr) instance_a = new T();

				return instance_a;
			}

			/** Explicitly close the singleton */
			static inline void close()
			{
				std::lock_guard<std::mutex> lck(mux_a);

				if (instance_a != nullptr) {
					delete instance_a;
					instance_a = nullptr;
				}
			}

			static inline bool is_constructed()
			{
				std::lock_guard<std::mutex> lck(mux_a);
				return instance_a != nullptr;
			}

	};

	template <class T> T *(Singleton<T>::instance_a) = nullptr;
	template <class T> std::mutex Singleton<T>::mux_a;

} // Fs2a namespace
