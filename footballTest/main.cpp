#include "stdafx.h"
#include <conio.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextOutputter.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	CppUnit::TextUi::TestRunner runner;

	CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
	runner.addTest(suite);
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),std::cerr));
	//runner.setOutputter(new CppUnit::TextOutputter(&runner.result(),std::cerr));


	runner.run();
	_getch();
	return 0;
}