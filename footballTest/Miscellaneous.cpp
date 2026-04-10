#include "stdafx.h"
#include "Miscellaneous.h"


CPPUNIT_TEST_SUITE_REGISTRATION(MiscellaneousTest);


void MiscellaneousTest::setUp()
{
}

void MiscellaneousTest::tearDown()
{
}


void MiscellaneousTest::testFoo()
{
   int32_t foo = 0xFFFFFFFF;
   CPPUNIT_ASSERT(foo == -1);
   CPPUNIT_ASSERT(foo == 0xFFFFFFFF);

   foo = 0xFFFFFFFE;
   CPPUNIT_ASSERT(foo == -2);
   CPPUNIT_ASSERT(foo == 0xFFFFFFFE);
}