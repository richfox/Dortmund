#pragma once
#include <memory>
#include "cppunit\TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

class Formation;

class FormationTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(FormationTest);
	CPPUNIT_TEST(test_defence_player);
	CPPUNIT_TEST(test_offense);
	CPPUNIT_TEST(test_defence);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void test_defence_player();
	void test_offense();
	void test_defence();

private:
	std::auto_ptr<Formation> _formation;
};