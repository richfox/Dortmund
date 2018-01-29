//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#pragma once
#include "cppunit\TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

class GuardTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(GuardTest);
   CPPUNIT_TEST(test);
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp()
   {}
   void tearDown()
   {}

   void test();
};