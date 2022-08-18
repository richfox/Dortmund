#include "stdafx.h"
#include "HeapTest.h"
#include "..\Container\Heap.h"


using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION(HeapTest);


void HeapTest::test()
{
   int seq[10] = {9,33,2,3,14,77,4,112,6,5};
   cout << "test min-heap\n";
   Heap heap;
   heap.Init();
   for (int i=0; i<10; i++)
   {
      heap.Insert(seq[i]);
   }
   heap.Print();
   CPPUNIT_ASSERT(heap.Head() == 2);

   int minelem = heap.Remove(1);
   heap.Print();
   CPPUNIT_ASSERT(heap.Head() == 3);

   heap.Decrease(2,1);
   heap.Print();
   CPPUNIT_ASSERT(heap.Head() == 1);
}