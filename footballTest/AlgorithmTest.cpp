#include "stdafx.h"
#include "AlgorithmTest.h"
#include "..\Algorithm\factorial.h"
#include "..\Algorithm\search.h"

using namespace std;
using namespace XFU;


CPPUNIT_TEST_SUITE_REGISTRATION(AlgoTest);


void AlgoTest::test()
{
   cout << "\r\ntest factorial...\r\n" << endl;

   CPPUNIT_ASSERT(XFU::Factorial<5>::value==XFU::fac(5));
   CPPUNIT_ASSERT(XFU::Factorial<4>::value==XFU::factorial(4));
   CPPUNIT_ASSERT(XFU::fac(3)==XFU::factorial(3));


   cout << "\r\ntest search...\r\n" << endl;

   static const std::vector<int> lucas = {1,3,4,7,11,18,29,47,76,123};
   CPPUNIT_ASSERT(search(lucas,0,int(lucas.size())-1,1) == 0);
   CPPUNIT_ASSERT(binary_search(lucas,0,int(lucas.size())-1,1) == 0);
   CPPUNIT_ASSERT(search(lucas,0,int(lucas.size())-1,29) == 6);
   CPPUNIT_ASSERT(binary_search(lucas,0,int(lucas.size())-1,29) == 6);
   CPPUNIT_ASSERT(search(lucas,0,int(lucas.size())-1,123) == 9);
   CPPUNIT_ASSERT(binary_search(lucas,0,int(lucas.size())-1,123) == 9);
   CPPUNIT_ASSERT(search(lucas,0,int(lucas.size())-1,2) == -1);
   CPPUNIT_ASSERT(binary_search(lucas,0,int(lucas.size())-1,2) == -1);
}