#include "stdafx.h"
#include "Miscellaneous.h"


CPPUNIT_TEST_SUITE_REGISTRATION(MiscellaneousTest);


void MiscellaneousTest::setUp()
{
}

void MiscellaneousTest::tearDown()
{
}


void MiscellaneousTest::testFoo()
{
   int32_t foo = 0xFFFFFFFF;
   CPPUNIT_ASSERT(foo == -1);
   CPPUNIT_ASSERT(foo == 0xFFFFFFFF);

   foo = 0xFFFFFFFE;
   CPPUNIT_ASSERT(foo == -2);
   CPPUNIT_ASSERT(foo == 0xFFFFFFFE);

   //1d range searching
   const std::map<int, const char*> m
    {
        {0, "zero"},
        {2, "two"},
        {3, "three"},
        {5, "five"}
    };
 
    int count = 0;
    auto p = m.equal_range(0);
    auto q = m.equal_range(5);
    for (auto& it = p.first; it != q.second; it++, count++)
    {
       it->first;
       it->second;
    }
    CPPUNIT_ASSERT(count == 4);

    count = 0;
    p = m.equal_range(0);
    q = m.equal_range(4);
    for (auto& it = p.first; it != q.second; it++, count++)
    {
       it->first;
       it->second;
    }
    CPPUNIT_ASSERT(count == 3);

    count = 0;
    p = m.equal_range(1);
    q = m.equal_range(5);
    for (auto& it = p.first; it != q.second; it++, count++)
    {
       it->first;
       it->second;
    }
    CPPUNIT_ASSERT(count == 3);

    count = 0;
    p = m.equal_range(1);
    q = m.equal_range(4);
    for (auto& it = p.first; it != q.second; it++, count++)
    {
       it->first;
       it->second;
    }
    CPPUNIT_ASSERT(count == 2);
}