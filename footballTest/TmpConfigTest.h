#pragma once


#pragma once
#include "cppunit\TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"


class TmpConfigTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(TmpConfigTest);
   CPPUNIT_TEST(test);
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp()
   {}

   void tearDown()
   {}

   void test();
};