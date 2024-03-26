#include "stdafx.h"
#include <conio.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextOutputter.h>
#include <iostream>
#include "Windows.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CppUnit::TextUi::TestRunner runner;

	CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
	runner.addTest(suite);
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),std::cerr));
	//runner.setOutputter(new CppUnit::TextOutputter(&runner.result(),std::cerr));


	runner.run();

	DWORD count = 0;
	std::wstring x = L"run unit test finished!!!";
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), x.c_str(), DWORD(x.length()), &count, 0);

	_getch();

	return 0;
}