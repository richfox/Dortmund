#include "stdafx.h"
#include "GenericTreeTest.h"
#include "..\Container\GenericTree.h"
#include "..\Container\DisjointSet.h"

using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION(GenericTreeTest);


void GenericTreeTest::test()
{
   /*   create a tree like below
    *              10
    *        /   /    \   \
    *        2  34    56   100
    *       / \         |   /  | \
    *      77  88       1   7  8  9
    */

   shared_ptr<TreeNode> root(new TreeNode(10));
   shared_ptr<TreeNode> node0(new TreeNode(2));
   root->_children.push_back(node0.get());
   shared_ptr<TreeNode> node1(new TreeNode(34));
   root->_children.push_back(node1.get());
   shared_ptr<TreeNode> node2(new TreeNode(56));
   root->_children.push_back(node2.get());
   shared_ptr<TreeNode> node3(new TreeNode(100));
   root->_children.push_back(node3.get());
   shared_ptr<TreeNode> leaf0(new TreeNode(77));
   root->_children[0]->_children.push_back(leaf0.get());
   shared_ptr<TreeNode> leaf1(new TreeNode(88));
   root->_children[0]->_children.push_back(leaf1.get());
   shared_ptr<TreeNode> leaf2(new TreeNode(1));
   root->_children[2]->_children.push_back(leaf2.get());
   shared_ptr<TreeNode> leaf3(new TreeNode(7));
   root->_children[3]->_children.push_back(leaf3.get());
   shared_ptr<TreeNode> leaf4(new TreeNode(8));
   root->_children[3]->_children.push_back(leaf4.get());
   shared_ptr<TreeNode> leaf5(new TreeNode(9));
   root->_children[3]->_children.push_back(leaf5.get());

   cout << "Level order traversal\n";
   level_order_traversal(root.get());

   cout << "lowest common ancestors algorithm\n";
   vector<Query> qs = {{1,2},{77,88},{9,2},{56,77},{2,1}};
   DisjointSetEx ds;
   LCA(root.get(),qs,ds);
}