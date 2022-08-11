#include "stdafx.h"
#include "GenericTree.h"
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

