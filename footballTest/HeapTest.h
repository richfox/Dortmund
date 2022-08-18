#pragma once
#include "cppunit\TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"


class HeapTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(HeapTest);
   CPPUNIT_TEST(test);
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp()
   {}

   void tearDown()
   {}

   void test();
};