#include "stdafx.h"
#include "AlgorithmTest.h"
#include "..\Algorithm\factorial.h"

using namespace std;
using namespace XFU;


CPPUNIT_TEST_SUITE_REGISTRATION(AlgoTest);


void AlgoTest::test()
{
   cout << "\r\ntest factorial...\r\n" << endl;

   CPPUNIT_ASSERT(XFU::Factorial<5>::value==XFU::fac(5));
   CPPUNIT_ASSERT(XFU::Factorial<4>::value==XFU::factorial(4));
   CPPUNIT_ASSERT(XFU::fac(3)==XFU::factorial(3));
}