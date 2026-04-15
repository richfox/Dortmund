#pragma once

#include <limits.h>
#include <vector>
#include <cmath>
#include <algorithm>
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


struct Interval
{
   Interval(int l, int u)
      :lower(l),
      upper(u)
   {}

   int lower, upper;
};


//一维区域查找，使用红黑树
std::vector<int> range_query(const std::map<int, const char*>& tree, const Interval& interval)
{
   std::vector<int> res;

   auto p = tree.equal_range(interval.lower);
   auto q = tree.equal_range(interval.upper);
   for (auto& it = p.first; it != q.second; it++)
   {
      res.push_back(it->first);
   }

   return res;
}

//构造区间树
BSTree<int>* constructIntervalTree(const std::vector<Interval>& intervals)
{
   if (intervals.empty())
      return nullptr;

   std::vector<int> tmp;
   tmp.reserve(intervals.size() * 2);
   for (const auto& i : intervals)
   {
      tmp.push_back(i.lower);
      tmp.push_back(i.upper);
   }
   int n = tmp.size() / 2 - 1;
   std::nth_element(tmp.begin(), tmp.begin() + n, tmp.end());
   int median = tmp[n];

   BSTree<int>* root = new BSTree<int>(median);

   std::vector<Interval> intervalsLeft;
   std::vector<Interval> intervalsMid;
   std::vector<Interval> intervalsRight;
   for (const auto& i : intervals)
   {
      if (i.upper < median)
         intervalsLeft.push_back(i);
      else if (i.lower > median)
         intervalsRight.push_back(i);
      else
         intervalsMid.push_back(i);
   }

   root->_lson = constructIntervalTree(intervalsLeft);
   root->_rson = constructIntervalTree(intervalsRight);

   return root;
}