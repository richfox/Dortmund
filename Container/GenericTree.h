#pragma once

#include <vector>


struct TreeNode
{
   int _key;
   std::vector<TreeNode*> _children;

   TreeNode(int key)
      :_key(key),
       _children()
   {}

   TreeNode(int key,std::vector<TreeNode*> children)
      :_key(key),
      _children(children)
   {}
};



void __declspec(dllexport) level_order_traversal(TreeNode* root);

struct Query
{
    int L, R;
};

class DisjointSetEx;

//Tarjan’s off-line lowest common ancestors algorithm
void __declspec(dllexport) LCA(const TreeNode* node,const std::vector<Query>& qs,DisjointSetEx& ds);