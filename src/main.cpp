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

#include <cstring>
#include <boost/program_options.hpp>
#include "Logger.h"

namespace po = boost::program_options;
using std::cerr, std::endl;

void help(const char *argv0)
{
	cerr << "Usage: " << basename(argv0) << " [-h|-o <outfile>|--output <outfile>]";
	cerr << " <datafile> <template>" << endl << endl;
	cerr << "This application reads <datafile> in JSON format (extension .json) or YAML format ";
	cerr << "(extension .yaml or .yml)" << endl;
	cerr << " and outputs the processing result of the template file in lcte format to stdout." << endl;
	cerr << "The lcte format is described on the github.com page at:" << endl;
	cerr << "https://github.com/hartogjr/lcte" << endl;
	cerr << "Options:" << endl;
	cerr << "-h                     Print this help" << endl;
	cerr << "-o|--output <outfile>  Write output to <outfile> instead of stdout." << endl;
	cerr << endl << "All errors (including this help) are written to stderr." << endl;
	exit(1);
}

int main(int argc, char *argv[])
{
	size_t strp = strlen(STR(REPOROOT))+1;
	Fs2a::Logger::instance()->stderror(strp);
	std::string outfile;

	try {
		po::options_description desc("C++ & Lua Template Engine command-line interface.\nCommand-line options:");
		desc.add_options()
			("help,h", "Show this help message on standard error")
			("output,o", po::value<std::string>(&outfile), "Set the output file instead of standard out")
			("syslog,s", "Log to syslog instead of standard error")
		;
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
		if (vm.count("help") {
			cerr << desc << endl;
			throw 0;
		}

		if (vm.count("syslog") {
			Fs2a::Logger::instance()->syslog("clite", LOG_USER, strp);
			LD("Logging to syslog (instead of stderror)");
		}

/*	do {
		switch (c = getopt_long(argc, argv, "ho:", opts, NULL)) {
			case -1: // End of options
				break;

			case 'o':
				outf.open(optarg);
				if (!outf.good()) {
					outf.close();
					cerr << "Error opening output file " << optarg << endl;
					exit(1);
				}
				break;

			default:
				help(argv[0]);
				break;

		}
	} while (c != -1);

	if (argc != 3) {
		cerr << "Invalid number of arguments " << argc-1;
		cerr << " given, should be 2 after parsing options." << endl;
		exit(1);
	}

	try {
		// Loadfile(argv[1]);
		if (outf.good()) {
			// ProcessTemplate(argv[2], outfile);
		} else {
			// ProcessTemplate(argv[2], std::cout);
		}
	} catch (std::exception & e) {
		cerr << "Exception: " << e.what() << endl;
		outfile.close();
		return 1;
	}

	outfile.close(); */

	} catch (const std::exception & se) {
		LE("Caught general exception: %s", se.what());
		return 1;
	} catch (const int & i) {
		return i;
	} catch (...) {
		LE("Uncaught exception occurred");
		return 1;
	}

	return 0;
}
