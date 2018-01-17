/** @author   Simon de Hartog <simon@fs2a.pro>
 * @copyright Fs2a Ltd. (c) 2017 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <iostream>
#include <string.h>
#include <globals.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace std;

/** Runs the check application.
 * @returns 0 on success, 1 if a check failed. */
int main(int argc, char *argv[])
{
	UNUSED(argc);
	Fs2a::Logger::instance()->open(basename(argv[0]), LOG_LOCAL0, strlen(REPOROOT) + 1);

	CppUnit::TextUi::TestRunner runner;
	bool retval = false;

	// Set up test suite
	CppUnit::TestFactoryRegistry & registry =
		CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());

	// Actually run all tests
	retval = runner.run();

	// Close logger again
	Fs2a::Logger::close();

	// Convert the C-style true (1) to Shell-style true (0) and v.v.
	return retval ? 0 : 1;
}
