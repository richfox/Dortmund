//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#pragma once
#include "cppunit\TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"


class ObjectStringTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(ObjectStringTest);
   CPPUNIT_TEST(test);
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp()
   {}

   void tearDown()
   {}

   void test();
};