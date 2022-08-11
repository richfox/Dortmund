#include "stdafx.h"
#include "GenericTree.h"
#include "DisjointSet.h"
#include <iostream>
#include <memory>
#include <queue>


using namespace std;



void level_order_traversal(TreeNode* root)
{
   if (root == nullptr)
        return;

    //using queue as assis data structure
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty())
    {
        size_t n = q.size();
 
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            TreeNode* node = q.front();
            q.pop();
            cout << node->_key << " ";
  
            // Enqueue all children of the dequeued item
            for (int i=0; i<node->_children.size(); i++)
            {
                q.push(node->_children[i]);
            }

            n--;
        }
  
        cout << endl;
    }
}



void LCA(const TreeNode* node,const vector<Query>& qs,DisjointSetEx& ds)
{
   int u = node->_key;
   ds.MakeSet(u);
   ds.ancestor[ds.FindSet(u)] = u;
   for (const TreeNode* child : node->_children)
   {
      LCA(child,qs,ds);
      int v = child->_key;
      ds.Union(u,v);
      ds.ancestor[ds.FindSet(u)] = u;
   }
   ds.color[u] = 1; //Black

   for (const Query q : qs)
   {
      if (q.L == u)
      {
         int v = q.R;
         if (ds.color[v] == 1)
         {
            cout << "the LCA of " << u << " and " << v << " is " << ds.ancestor[ds.FindSet(v)] << endl;
         }
      }
      else if (q.R == u)
      {
         int v = q.L;
         if (ds.color[v] == 1)
         {
            cout << "the LCA of " << u << " and " << v << " is " << ds.ancestor[ds.FindSet(v)] << endl;
         }
      }
   }
}
