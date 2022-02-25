#pragma once

#include <limits.h>
#include <vector>
#include <cmath>
#include "..\Container\BSTree.h"



int value_of_seq(const std::vector<int>& seq,int i)
{
   if (i <= seq.size() - 1)
      return seq[i];
   else
      return INT_MAX;
}

//递归线性搜索算法，O(n)
//如果有x，返回数列中x的位置，否则为-1
int search(const std::vector<int>& seq,int start,int end,int x)
{
   if (value_of_seq(seq,start) == x)
      return start;
   else if (start == end)
      return -1;
   else
      return search(seq,start+1,end,x);
}

//递归二分搜索算法，O(logn)
//如果有x，返回数列中x的位置，否则为-1，输入数列必须升序排列
int binary_search(const std::vector<int>& seq,int start,int end,int x)
{
   int m = (int)floor((start + end) / 2);
   if (value_of_seq(seq,m) == x)
      return m;
   else if (x<value_of_seq(seq,m) && start<m)
      return binary_search(seq,start,m-1,x);
   else if (x>value_of_seq(seq,m) && end>m)
      return binary_search(seq,m+1,end,x);
   else
      return -1;
}


//二叉树搜索算法，最好情况Ω(h=⌈log(n+1)⌉)，其中n为树的顶点数量(包括node和leaf)h为树的高度，
//如果是平衡二叉树，则最差情况O(h=⌈log(n+1)⌉)
bool binary_tree_search(const BSTree<int>& tree,int x)
{
   if (tree.Search(x))
      return true;

   return false;
}
