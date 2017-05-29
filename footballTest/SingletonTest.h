#pragma once


#include "..\DesignPattern\Singleton.h"
#include "cppunit\TestFixture.h"
#include "cppunit\extensions\HelperMacros.h"



class FOO
{
public:
   static int _count;

   static FOO& insideInstance()
   {
      return XFU::CreateUsingStatic<FOO>::get_T_singleton();
   }

   std::map<int,int> temp;

private:
   FOO()
   {
      _count++;
   }

   ~FOO()
   {
      _count--;
   }

   
   friend struct XFU::CreateUsingStatic<FOO>;

   friend FOO& get_static_singleton();

   friend struct Loki::CreateUsingNew<FOO>;
};

int FOO::_count = 0;

FOO& get_static_singleton()
{
   static FOO t;
   return t;
}



class SingletonTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(SingletonTest);
   CPPUNIT_TEST(testSingletonAtHeap);
   CPPUNIT_TEST(testSingletonAtStack);
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void testSingletonAtHeap();
   void testSingletonAtStack();
};