/** @author   Simon de Hartog <simon@fs2a.pro>
 * @copyright Fs2a Ltd. (c) 2018
 * vim:set ts=2 sw=2 noexpandtab: */

#include <iostream>
#include <cstdarg>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "Logger.h"

namespace Fs2a {

	Logger::Logger()
		: strip_a(0), syslog_a(false)
	{
		levels_a[LOG_EMERG]  ="EMERGENCY";
		levels_a[LOG_ALERT]  ="ALERT";
		levels_a[LOG_CRIT]   ="CRITICAL";
		levels_a[LOG_ERR]    ="ERROR";
		levels_a[LOG_WARNING]="WARNING";
		levels_a[LOG_NOTICE] ="NOTICE";
		levels_a[LOG_INFO]   ="INFO";
		levels_a[LOG_DEBUG]  ="DEBUG";
	}

	Logger::~Logger()
	{
		std::lock_guard<std::mutex> lck(mymux_a);

		if (syslog_a) {
			closelog();
			syslog_a = false;
		}
	}

	void Logger::log(
		const std::string & file_i,
		const size_t & line_i,
		const int priority_i,
		const char *fmt_i,
		...
	)
	{
		va_list args;         // Variable arguments list
		char buf[BUFSIZ];     // Buffer to store log string
		size_t count = 0;     // Number of percent signs in fmt_i
		std::string fmt;      // Separate format string for counting
		int offset = 0;       // Offset to continue string printing
		std::ostringstream oss; // Output Stringstream to write Thread ID to
		size_t pos = 0;       // Position in string of character
		struct timeval tv;    // Time value storage
		struct tm timeParts;  // Different parts of current time

		if (fmt_i == nullptr) return;

		fmt.assign(fmt_i);

		gettimeofday(&tv, nullptr);
		gmtime_r(&(tv.tv_sec), &timeParts);
		oss << std::this_thread::get_id();

		offset = sprintf(
					 buf,
					 "%02d:%02d:%02d.%06ld [%s] %s:%ld ",
					 timeParts.tm_hour,
					 timeParts.tm_min,
					 timeParts.tm_sec,
					 tv.tv_usec,
					 oss.str().c_str(),
					 file_i.substr(strip_a).c_str(),
					 line_i
				 );

		if (!syslog_a) {
			strcpy(buf+offset, levels_a[priority_i].c_str());
			offset += levels_a[priority_i].length();
			buf[offset++] = ' ';
		}

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
			vsprintf(buf + offset, fmt_i, args);
			va_end(args);
		}
		else {
			strcpy(buf + offset, fmt_i);
		}

		if (syslog_a) {
			::syslog(priority_i, "%s", buf);
		} else {
			std::cerr << buf << std::endl;
		}

		return;
	}

	void Logger::stderror(const size_t strip_i)
	{
		std::lock_guard<std::mutex> lck(mymux_a);

		if (syslog_a) {
			closelog();
			syslog_a = false;
		}
		strip_a = strip_i;
	}

	bool Logger::syslog(const std::string ident_i, const int facility_i, const size_t strip_i)
	{
		std::lock_guard<std::mutex> lck(mymux_a);

		if (syslog_a) return false;

		ident_a = ident_i;
		strip_a = strip_i;

		openlog(ident_a.c_str(), LOG_CONS | LOG_NDELAY | LOG_PID, facility_i);
		syslog_a = true;
		return true;
	}

} // Fs2a namespace
