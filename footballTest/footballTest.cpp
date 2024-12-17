// footballTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "footballTest.h"
#include ".\..\football\football.h"
#include ".\..\Container\Bitmap.h"


CPPUNIT_TEST_SUITE_REGISTRATION(FormationTest);

void FormationTest::setUp()
{
	_formation.reset(new Formation(L"433"));

	_formation->set_defence_player(4);
	_formation->set_midfield_player(3);
	_formation->set_forward_player(3);
}

void FormationTest::tearDown()
{
	_formation.reset();
}

void FormationTest::test_defence_player()
{
	int total_player = _formation->get_defence_player() + _formation->get_midfield_player() + _formation->get_forward_player();
	CPPUNIT_ASSERT(total_player == 10);
}

void FormationTest::test_offense()
{
	CPPUNIT_ASSERT(_formation->get_forward_player() == 3);
}

void FormationTest::test_defence()
{
	CPPUNIT_ASSERT(_formation->get_defence_player() == 4);
}


void FormationTest::test_other()
{
   g_mark;
   set_mark(Marking::FIRST, true);
   CPPUNIT_ASSERT(g_mark == Marking::FIRST);
   set_mark(Marking::SECOND, true);
   CPPUNIT_ASSERT(g_mark == 0x03);

   CPPUNIT_ASSERT(is_marked(Marking::FIRST) == true);
   CPPUNIT_ASSERT(is_marked(Marking::FOURTH) == false);

   set_mark(Marking::FIRST, false);

   CPPUNIT_ASSERT(is_marked(Marking::FIRST) == false);
   CPPUNIT_ASSERT(is_marked(Marking::SECOND) == true);
   CPPUNIT_ASSERT(is_marked(Marking::FOURTH) == false);
}



