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

#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "Logger.h"

namespace Fs2a {

	Logger::Logger()
		: maxlevel_a(Logger::debug), stream_a(nullptr), strip_a(0), syslog_a(false)
	{
		levels_a[error]   = "ERROR";
		levels_a[warning] = "WARNING";
		levels_a[notice]  = "NOTICE";
		levels_a[info]    = "INFO";
		levels_a[debug]   = "DEBUG";
	}

	Logger::~Logger()
	{
		GRD(mymux_a);

		if (syslog_a) {
			closelog();
			syslog_a = false;
		} else stream_a = nullptr;
	}

	std::unique_ptr<std::string> Logger::log(
		const std::string & file_i,
		const size_t & line_i,
		const loglevel_t priority_i,
		const char *fmt_i,
		...
	)
	{
		va_list args;           // Variable arguments list
		char buf[BUFSIZ];       // Char buffer for doing vsnprintf
		size_t count = 0;       // Number of percent signs in fmt_i
		std::string fmt;        // Separate format string for counting
		std::ostringstream oss; // Output Stringstream to write log string to
		size_t pos = 0;         // Position in string of character
		struct timeval tv;      // Time value storage
		struct tm timeParts;    // Different parts of current time

		if (fmt_i == nullptr) return std::unique_ptr<std::string>();

		if (priority_i > maxlevel_a) return std::unique_ptr<std::string>();

		fmt.assign(fmt_i);

		gettimeofday(&tv, nullptr);
		gmtime_r(&(tv.tv_sec), &timeParts);

		oss << std::setfill('0') << std::setw(2) << timeParts.tm_hour << ':';
		oss << std::setfill('0') << std::setw(2) << timeParts.tm_min << ':';
		oss << std::setfill('0') << std::setw(2) << timeParts.tm_sec << '.';
		oss << std::setfill('0') << std::setw(6) << tv.tv_usec;
		oss << " [" << std::this_thread::get_id() << "] ";
		oss << file_i.substr(strip_a) << ':';
		oss << std::setw(0) << line_i << ' ';

		if (!syslog_a) oss << levels_a[priority_i] << ' ';

		// Remove double percent signs
		while ((pos = fmt.find("%%")) != std::string::npos) fmt.erase(pos, 2);

		// Now count remaining percent signs to know number of args
		pos = 0;

		while ((pos = fmt.find('%', pos)) != std::string::npos) {
			count++;
			pos++;
		}

		if (count > 0) {
			va_start(args, count);
			size_t rv = vsnprintf(buf, BUFSIZ, fmt_i, args);
			va_end(args);
			fmt.assign(buf);

			if (rv >= BUFSIZ) fmt += " (truncated)";
		} else {
			fmt.assign(fmt_i);
		}

		// Now remove double percent signs
		pos = fmt.find("%%");
		while (pos != std::string::npos) {
			fmt.erase(pos, 1); 
			pos = fmt.find("%%", pos+1);
		}

		// And add to stringstream to output
		oss << fmt;

		if (syslog_a) {
			::syslog(priority_i, "%s", oss.str().c_str());
		}
		else {
			if (stream_a == nullptr) {
				throw std::logic_error("Asked to log to stream, but stream is NULL");
			}
			*stream_a << oss.str() << std::endl;
		}

		return std::unique_ptr<std::string>(new std::string(oss.str()));
	}

	void Logger::stream(std::ostream * stream_i, const size_t strip_i)
	{
		if (stream_i == nullptr) {
			throw std::invalid_argument("Unable to write log output to NULL stream pointer");
		}

		GRD(mymux_a);

		if (syslog_a) {
			closelog();
			syslog_a = false;
		}

		strip_a = strip_i;

		stream_a = stream_i;
	}

	bool Logger::syslog(const std::string ident_i, const int facility_i, const size_t strip_i)
	{
		GRD(mymux_a);

		if (syslog_a) return false;

		ident_a = ident_i;
		strip_a = strip_i;

		openlog(ident_a.c_str(), LOG_CONS | LOG_NDELAY | LOG_PID, facility_i);
		stream_a = nullptr;
		syslog_a = true;
		return true;
	}

} // Fs2a namespace
