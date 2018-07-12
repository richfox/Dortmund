#pragma once


#include "cppunit\TestFixture.h"
#include "cppunit\extensions\HelperMacros.h"


class MiscellaneousTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(MiscellaneousTest);
   CPPUNIT_TEST(testFoo);
   CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

    void testFoo();

private:
};