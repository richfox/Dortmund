#include "stdafx.h"
#include "BSTreeTest.h"
#include "..\Container\BSTree.h"

using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION(BSTreeTest);


void BSTreeTest::test()
{
   cout << "\r\ntest Binary Search Tree...\r\n" << endl;

   vector<int> testvec{1,2,3,5,6};
   BSTree<int> tree(0);
   for (const int i : testvec)
   {
      tree.Insert(i);
   }
   CPPUNIT_ASSERT(tree.CountOfVetex() == 6);

   auto res = tree.PreOrder();
   CPPUNIT_ASSERT(res == vector<int>({0,1,2,3,5,6}));

   res = tree.PostOrder();
   CPPUNIT_ASSERT(res == vector<int>({6,5,3,2,1,0}));

   auto* ptree = tree.Insert(4);
   CPPUNIT_ASSERT(ptree->_element == 4);
   CPPUNIT_ASSERT(!ptree->_lson);
   CPPUNIT_ASSERT(!ptree->_rson);
   res = tree.InOrder();
   CPPUNIT_ASSERT(res == vector<int>({0,1,2,3,4,5,6}));
   CPPUNIT_ASSERT(tree.CountOfVetex() == 7);
}