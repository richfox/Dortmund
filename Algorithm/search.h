#pragma once

#include <limits.h>
#include <vector>
#include <cmath>




int value_of_seq(const std::vector<int>& seq,int i)
{
   if (i <= seq.size() - 1)
      return seq[i];
   else
      return INT_MAX;
}

//线性搜索，O(n)
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

//二分搜索，O(logn)
//如果有x，返回数列中x的位置，否则为-1
int binary_search(const std::vector<int>& seq,int i,int j,int x)
{
   int m = (int)floor((i + j) / 2);
   if (value_of_seq(seq,m) == x)
      return m;
   else if (x<value_of_seq(seq,m) && i<m)
      return binary_search(seq,i,m-1,x);
   else if (x>value_of_seq(seq,m) && j>m)
      return binary_search(seq,m+1,j,x);
   else
      return -1;
}