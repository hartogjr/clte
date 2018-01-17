/** @author   Simon de Hartog <simon@fs2a.pro>
 * @copyright Fs2a Ltd. (c) 2018 */

#pragma once

#include <map>
#include <syslog.h>
#include "Singleton.h"

/** @{ Logging macros for easy logging */

/// Log a debug message
#define LD(fmt, ...) \
	Fs2a::Logger::instance()->log(__FILE__, __LINE__, LOG_DEBUG, fmt, ##__VA_ARGS__)

/// Log an informational message
#define LI(fmt, ...) \
	Fs2a::Logger::instance()->log(__FILE__, __LINE__, LOG_INFO, fmt, ##__VA_ARGS__)

/// Log a warning message
#define LW(fmt, ...) \
	Fs2a::Logger::instance()->log(__FILE__, __LINE__, LOG_WARNING, fmt, ##__VA_ARGS__)

/// Log an error message
#define LE(fmt, ...) \
	Fs2a::Logger::instance()->log(__FILE__, __LINE__, LOG_ERR, fmt, ##__VA_ARGS__)
/** @} */

class LoggerCheck;

namespace Fs2a {

	class Logger : public Fs2a::Singleton<Logger> {
			/// Singleton template as friend for construction
			friend class Fs2a::Singleton<Logger>;

			/// Check class is also a friend
			friend class ::LoggerCheck;

		private:
			/// Default constructor
			Logger();

			/// Copy constructor
			Logger(const Logger & obj_i) = delete;

			/// Assignment constructor
			Logger & operator=(const Logger & obj_i) = delete;

			/// Destructor
			~Logger();

		protected:
			/** Maintain a local string for syslog program identification,
			 * because openlog does not copy it. */
			std::string ident_a;

			/// Textual syslog levels map.
			std::map<int, std::string> levels_a;

			/// Internal mutex to be MT safe
			std::mutex mymux_a;

			/// Characters to strip from beginning of filenames
			size_t strip_a;

			/// True when logging to syslog, false when logging to stderr
			bool syslog_a;

		public:
			/** Check whether the current logging destination is syslog.
			 * @returns True if logging to syslog, false if logging to
			 * stderr. */
			inline bool destSyslog() const { return syslog_a; }

			/** Convenience syslogging function. Please call the appropriate logging
			 * macros instead of this method.
			 * @param file_i Filename we are logging from
			 * @param line_i Line number at which we are logging
			 * @param priority_i Syslog priority level
			 * @param fmt_i Format argument for remainder of arguments */
			void log(
				const std::string & file_i,
				const size_t & line_i,
				const int priority_i,
				const char *fmt_i,
				...
			);

			/** Write all subsequent logs to stderr.
			 * @param strip_i Number of characters to strip from beginning of
			 * filenames to shorten log output, default 0 */
			void stderror(const size_t strip_i = 0);

			/** Write all following logs to syslog with specified program name.
			 * @param ident_i Program identification
			 * @param facility_i Syslog facility to use as specified in the
			 * syslog(3) manual page (man 3 syslog), default LOG_LOCAL0
			 * @param strip_i Number of characters to strip from beginning of
			 * filenames to short log output, default 0
			 * @returns True if succeeded, false if already opened. */
			bool syslog(const std::string ident_i, const int facility_i = LOG_LOCAL0, const size_t strip_i = 0);

	};

} // Fs2a namespace
