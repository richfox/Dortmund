
#include "stdafx.h"
#include "SingletonTest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(SingletonTest);


void SingletonTest::setUp()
{}

void SingletonTest::tearDown()
{}


void SingletonTest::testSingletonAtHeap()
{
   XFU::get_T_singleton_pointer<FOO>();
   CPPUNIT_ASSERT(FOO::_count == 1);

   XFU::get_T_singleton_pointer<FOO>();
   CPPUNIT_ASSERT(FOO::_count == 1);
}

void SingletonTest::testSingletonAtStack()
{
   XFU::CreateUsingStatic<FOO>::get_T_singleton();
   CPPUNIT_ASSERT(FOO::_count == 2);

   XFU::CreateUsingStatic<FOO>::get_T_singleton();
   CPPUNIT_ASSERT(FOO::_count == 2);

   get_static_singleton();
   CPPUNIT_ASSERT(FOO::_count == 3);

   XFU::get_T_singleton_pointer<FOO>();
   CPPUNIT_ASSERT(FOO::_count == 3);

   std::map<int,int> ttt;
   for (int i=0; i<100; i++)
      ttt[i] = i;
   XFU::CreateUsingStatic<FOO>::get_T_singleton().temp = ttt;

   for (int i=0; i<100; i++)
      FOO::insideInstance();

   CPPUNIT_ASSERT(FOO::_count == 3);
}