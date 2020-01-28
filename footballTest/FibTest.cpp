//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################


#include "stdafx.h"
#include "FibTest.h"
#include "..\Algorithm\fib.h"
#include "..\Tool\Time.h"



using namespace std;
using namespace XFU;

CPPUNIT_TEST_SUITE_REGISTRATION(FibTest);


void FibTest::test()
{
   for (int i=0; i<_countof(fib); i++)
   {
      CPPUNIT_ASSERT(fibonacci(i) == fib[i]);
      CPPUNIT_ASSERT(dynamic_fibonacci(i) == fib[i]);
   }

   CPPUNIT_ASSERT(fibonacci(10) > dynamic_fibonacci(8));
   CPPUNIT_ASSERT(fibonacci(10) == dynamic_fibonacci(10));
   CPPUNIT_ASSERT(fibonacci(10) < dynamic_fibonacci(12));

   auto elapsed = time_call([&]()
   {
      dynamic_fibonacci(100);
   });
}