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