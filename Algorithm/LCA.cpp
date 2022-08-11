#include "stdafx.h"
#include "LCA.h"
#include "..\Container\GenericTree.h"
#include "..\Container\DisjointSet.h"
#include <iostream>

using namespace std;




void LCA(const TreeNode* node,DisjointSetEx& ds,const std::vector<Query>& qs)
{
   int u = node->_key;
   ds.MakeSet(u);
   ds.ancestor[ds.FindSet(u)] = u;
   for (const TreeNode* child : node->_children)
   {
      LCA(child,ds,qs);
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
