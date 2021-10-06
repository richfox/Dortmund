#include "stdafx.h"
#include "AlgorithmTest.h"
#include "..\Algorithm\factorial.h"
#include "..\Algorithm\search.h"
#include "..\Algorithm\sort.h"
#include "..\Algorithm\divide-and-conquer.h"
#include "..\Algorithm\backtracking.h"
#include "..\Container\BSTree.h"

using namespace std;
using namespace XFU;
using namespace xfu;


CPPUNIT_TEST_SUITE_REGISTRATION(AlgoTest);


void AlgoTest::test()
{
   cout << "\r\ntest factorial...\r\n" << endl;

   CPPUNIT_ASSERT(XFU::Factorial<5>::value==XFU::fac(5));
   CPPUNIT_ASSERT(XFU::Factorial<4>::value==XFU::factorial(4));
   CPPUNIT_ASSERT(XFU::fac(3)==XFU::factorial(3));


   cout << "\r\ntest search...\r\n" << endl;

   static const std::vector<int> lucas = {1,3,4,7,11,18,29,47,76,123};
   CPPUNIT_ASSERT(search(lucas,0,int(lucas.size())-1,1) == 0);
   CPPUNIT_ASSERT(binary_search(lucas,0,int(lucas.size())-1,1) == 0);
   CPPUNIT_ASSERT(search(lucas,0,int(lucas.size())-1,29) == 6);
   CPPUNIT_ASSERT(binary_search(lucas,0,int(lucas.size())-1,29) == 6);
   CPPUNIT_ASSERT(search(lucas,0,int(lucas.size())-1,123) == 9);
   CPPUNIT_ASSERT(binary_search(lucas,0,int(lucas.size())-1,123) == 9);
   CPPUNIT_ASSERT(search(lucas,0,int(lucas.size())-1,2) == -1);
   CPPUNIT_ASSERT(binary_search(lucas,0,int(lucas.size())-1,2) == -1);

   BSTree<int> tree(lucas.front());
   for (std::vector<int>::const_iterator it=lucas.begin()+1; it!=lucas.end(); it++)
   {
      tree.Insert(*it);
   }
   CPPUNIT_ASSERT(binary_tree_search(tree,16) == false);
   CPPUNIT_ASSERT(binary_tree_search(tree,18) == true);


   cout << "\r\ntest sorting...\r\n" << endl;

   static const std::vector<int> testseq = {1,3,5,7,8,1,9,2,4,6};
   CPPUNIT_ASSERT(merge_sort(testseq) == std::vector<int>({1,1,2,3,4,5,6,7,8,9}));
   auto copyseq = testseq;
   CPPUNIT_ASSERT(bubble_sort(copyseq) == std::vector<int>({1,1,2,3,4,5,6,7,8,9}));
   copyseq = testseq;
   CPPUNIT_ASSERT(insertion_sort(copyseq) == std::vector<int>({1,1,2,3,4,5,6,7,8,9}));
   copyseq = testseq;
   CPPUNIT_ASSERT(quick_sort(copyseq) == std::vector<int>({1,1,2,3,4,5,6,7,8,9}));
   copyseq = testseq;
   CPPUNIT_ASSERT(shaker_sort(copyseq) == std::vector<int>({1,1,2,3,4,5,6,7,8,9}));


   std::vector<int> testseq2 = {-2,4,-1,3,5,-6,1,2};
   CPPUNIT_ASSERT(find_largest_sum(testseq2) == 11);
   CPPUNIT_ASSERT(brute_force_find_largest_sum(testseq2) == 11);
   testseq2 = {4,1,-3,7,-1,-5,3,-2};
   CPPUNIT_ASSERT(find_largest_sum(testseq2) == 9);
   CPPUNIT_ASSERT(brute_force_find_largest_sum(testseq2) == 9);
   testseq2 = {-1,6,3,-4,-5,8,-1,7};
   CPPUNIT_ASSERT(find_largest_sum(testseq2) == 14);
   CPPUNIT_ASSERT(brute_force_find_largest_sum(testseq2) == 14);


   cout << "\r\ntest backtracking...\r\n" << endl;
   place_queen(0,4);
   CPPUNIT_ASSERT(xfu::count == 2);
}