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

   CPPUNIT_ASSERT(tree.Minimum()->_element == 0);
   CPPUNIT_ASSERT(tree.Maximum()->_element == 6);

   auto res = tree.PreOrder();
   CPPUNIT_ASSERT(res == vector<int>({0,1,2,3,5,6}));

   res = tree.PostOrder();
   CPPUNIT_ASSERT(res == vector<int>({6,5,3,2,1,0}));

   auto* ptree = tree.Insert(4);
   CPPUNIT_ASSERT(ptree->_element == 4);
   CPPUNIT_ASSERT(!ptree->_lson);
   CPPUNIT_ASSERT(!ptree->_rson);
   ptree = tree.Insert(2);
   CPPUNIT_ASSERT(ptree->_element == 2);
   CPPUNIT_ASSERT(!ptree->_lson);
   CPPUNIT_ASSERT(ptree->_rson->_element == 3);
   CPPUNIT_ASSERT(ptree->_parent->_element == 1);
   res = tree.InOrder();
   CPPUNIT_ASSERT(res == vector<int>({0,1,2,3,4,5,6}));
   CPPUNIT_ASSERT(tree.CountOfVetex() == 7);
   auto node = tree.Search(1);
   CPPUNIT_ASSERT(const_cast<BSTree<int>*>(node)->Successor()->_element == 2);
   CPPUNIT_ASSERT(const_cast<BSTree<int>*>(node)->Predecessor()->_element == 0);

   for (const int i : {-1,-2,-3,-4,-5})
   {
      tree.Insert(i);
   }
   CPPUNIT_ASSERT(tree.CountOfVetex() == 12);
   CPPUNIT_ASSERT(tree._lson->_element == -1);
   CPPUNIT_ASSERT(tree._lson->_parent->_element == 0);
   CPPUNIT_ASSERT(tree._rson->_element == 1);
   CPPUNIT_ASSERT(tree._rson->_parent->_element == 0);
   CPPUNIT_ASSERT(tree.Minimum()->_element == -5);
   CPPUNIT_ASSERT(tree.Maximum()->_element == 6);
   node = tree.Search(-1);
   CPPUNIT_ASSERT(const_cast<BSTree<int>*>(node)->Successor()->_element == 0);
   CPPUNIT_ASSERT(const_cast<BSTree<int>*>(node)->Predecessor()->_element == -2);

   tree.Delete(1);
   CPPUNIT_ASSERT(tree.CountOfVetex() == 11);
   CPPUNIT_ASSERT(tree._lson->_element == -1);
   CPPUNIT_ASSERT(tree._lson->_parent->_element == 0);
   CPPUNIT_ASSERT(tree._rson->_element == 2);
   CPPUNIT_ASSERT(tree._rson->_parent->_element == 0);
   tree.Delete(-5);
   CPPUNIT_ASSERT(tree.CountOfVetex() == 10);
   CPPUNIT_ASSERT(tree._lson->_element == -1);
   CPPUNIT_ASSERT(tree._lson->_parent->_element == 0);
   CPPUNIT_ASSERT(tree._rson->_element == 2);
   CPPUNIT_ASSERT(tree._rson->_parent->_element == 0);
   node = tree.Search(-4);
   CPPUNIT_ASSERT(!node->_lson);
   CPPUNIT_ASSERT(!node->_rson);
   CPPUNIT_ASSERT(node->_parent->_element == -3);
   tree.Delete(0);
   CPPUNIT_ASSERT(tree.CountOfVetex() == 9);
   CPPUNIT_ASSERT(tree._lson->_element == -1);
   CPPUNIT_ASSERT(tree._lson->_parent->_element == 2);
   CPPUNIT_ASSERT(tree._rson->_element == 3);
   CPPUNIT_ASSERT(tree._rson->_parent->_element == 2);
}