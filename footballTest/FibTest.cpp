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
   cout << "\r\ntest fibonacci sequence...\r\n" << endl;

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

   CPPUNIT_ASSERT(iterative_fibonacci(4) == dynamic_fibonacci(4));
   CPPUNIT_ASSERT(iterative_fibonacci(4) < dynamic_fibonacci(5));

   CPPUNIT_ASSERT(matrix_fibonacci(1) == fibonacci(1));
   CPPUNIT_ASSERT(matrix_fibonacci(10) == dynamic_fibonacci(10));

   CPPUNIT_ASSERT(formula_fibonacci(1) == fibonacci(1));
   CPPUNIT_ASSERT(formula_fibonacci(6) == dynamic_fibonacci(6));
}