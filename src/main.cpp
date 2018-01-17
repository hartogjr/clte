/** @author  Simon de Hartog <simon@fs2a.pro>
 * @copyright Fs2a Ltd. (c) 2018
 * vim:set ts=2 sw=2 noexpandtab: */

#include <iostream>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include "Driver.h"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <string.h>

using std::cerr, std::endl;

const struct options opts[3] = {
	{ "help",   no_argument,       NULL, 'h'  },
	{ "output", required_argument, NULL, 'o'  },
	{ NULL,     0,                 NULL, 0    }
};

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
	Clte::Driver driver;

	int c;

	std::ofstream outf;

	do {
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
		if (outfile.good()) {
			// ProcessTemplate(argv[2], outfile);
		} else {
			// ProcessTemplate(argv[2], std::cout);
		}
	} catch (std::exception & e) {
		cerr << "Exception: " << e.what() << endl;
		if (outfile.good()) outfile.close();
		return 1;
	}

	if (outfile.good()) outfile.close();
	return 0;
}
