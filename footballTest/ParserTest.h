//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#pragma once
#include <memory>
#include "cppunit\TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"




class ParserTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(ParserTest);
   CPPUNIT_TEST(testTokenizer);
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void testTokenizer();
};