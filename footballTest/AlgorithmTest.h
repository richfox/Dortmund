#pragma once


#pragma once
#include "cppunit\TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"


class AlgoTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(AlgoTest);
   CPPUNIT_TEST(test);
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp()
   {}

   void tearDown()
   {}

   void test();
};