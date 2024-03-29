﻿#pragma once

#include <vector>
#include <algorithm>
#include "..\Container\Heap.h"



//冒泡排序，O(n^2)
std::vector<int> bubble_sort(std::vector<int>& L)
{
   if (L.size() == 1)
      return L;
   
   for (int i=1; i<=L.size()-1; i++)
   {
      for (int j=1; j<=L.size()-i; j++)
      {
         if (L[j-1] > L[j])
         {
            int tmp = L[j-1];
            L[j-1] = L[j];
            L[j] = tmp;
         }
      }
   }
   return L;
}

//插入排序，O(n^2)
std::vector<int> insertion_sort(std::vector<int>& L)
{
   if (L.size() == 1)
      return L;

   for (int j=2; j<=L.size(); j++)
   {
      int i = 1;
      while (L[j-1] > L[i-1])
      {
         i += 1;
      }
      int m = L[j-1];
      for (int k=0; k<=j-i-1; k++)
      {
         L[j-k-1] = L[j-k-2];
      }
      L[i-1] = m;
   }
   return L;
}


//剃须刀排序，O(n^2)
std::vector<int> shaker_sort(std::vector<int>& L)
{
   int front = 1;
   int back = int(L.size());
   bool stillrun = true;
   while (front<back && stillrun)
   {
      if ((int(L.size())+back+front) % 2)
      {
         /*is odd then process from front to back*/
         stillrun = false;
         for (int j=front; j<=back-1; j++)
         {
            if (L[j-1] > L[j])
            {
               stillrun = true;
               int tmp = L[j-1];
               L[j-1] = L[j];
               L[j] = tmp;
            }
         }
         back -= 1;
      }
      else
      {
         /*process from back to front*/
         stillrun = false;
         for (int j=back; j>=front+1; j--)
         {
            if (L[j-2] > L[j-1])
            {
               stillrun = true;
               int tmp = L[j-2];
               L[j-2] = L[j-1];
               L[j-1] = tmp;
            }
         }
         front += 1;
      }
   }

   return L;
}


//快速排序，O(nlogn)
std::vector<int> quick_sort(std::vector<int>& L)
{
   if (L.size() == 1)
      return L;

   std::vector<int> L1;
   std::vector<int> L2;
   int tmp = L[0];
   for (int i=2; i<=L.size(); i++)
   {
      if (L[i-1] < L[0])
         L1.push_back(L[i-1]);
      else
         L2.push_back(L[i-1]);
   }

   if (!L1.empty())
      quick_sort(L1);
   if (!L2.empty())
      quick_sort(L2);
   
   for (int i=1; i<=L1.size(); i++)
   {
      L[i-1] = L1[i-1];
   }
   L[L1.size()] = tmp;
   for (int i=1; i<=L2.size(); i++)
   {
      L[L1.size()+i] = L2[i-1];
   }

   return L;
}

int partition(std::vector<int>& L,int l,int r)
{
   int pivot = L[r-1];
   int i = l-1;
   for (int j=l; j<r; j++)
   {
      if (L[j-1] <= pivot)
      {
         i++;
         int tmp = L[j-1];
         L[j-1] = L[i-1];
         L[i-1] = tmp;
         
      }
   }
   L[r-1] = L[i];
   L[i] = pivot;
   return i+1;
}

std::vector<int> quick_sort2(std::vector<int>& L,int l,int r)
{
   if (l < r)
   {
      int mid = partition(L,l,r);
      quick_sort2(L,l,mid-1);
      quick_sort2(L,mid+1,r);
   }
   return L;
}


//归并排序，O(nlogn)
std::vector<int> merge(std::vector<int>& L1,std::vector<int>& L2)
{
   std::vector<int> L;
   L.reserve(L1.size() + L2.size());

   while (!L1.empty() && !L2.empty())
   {
      if (L1.front() <= L2.front())
      {
         L.push_back(L1.front());
         L1.erase(L1.begin());
         if (L1.empty())
         {
            L.insert(L.end(),L2.begin(),L2.end());
            L2.clear();
         }
      }
      else
      {
         L.push_back(L2.front());
         L2.erase(L2.begin());
         if (L2.empty())
         {
            L.insert(L.end(),L1.begin(),L1.end());
            L1.clear();
         }
      }
   }
   return L;
}


std::vector<int> merge_sort(const std::vector<int>& L)
{
   if (L.size() == 1)
      return L;

   std::size_t m = L.size() / 2;
   std::vector<int> L1(L.begin(),L.begin()+m);
   std::vector<int> L2(L.begin()+m,L.end());
   return merge(merge_sort(L1),merge_sort(L2));
}


//堆排序，O(nlogn)
std::vector<int> heap_sort(std::vector<int>& L)
{
   Heap heap;
   heap.Init();

   //建堆，O(n)
   for (int i=0; i<L.size(); i++)
   {
      heap.Insert(L[i]);
   }

   //排序，O((n-1)logn)
   int i = 0;
   while (!heap.IsEmpty())
   {
      L[i++] = heap.Remove(1);
   }

   return L;
}


//计数排序（假设A中的每一个元素都是介于0到max之间的整数）, O(n)
std::vector<int> counting_sort(const std::vector<int>& A)
{
   std::vector<int> B(A.size(),-1);

   //找出最大值
   int k = *(std::max_element(A.begin(),A.end()));

   //用于计数的临时存储区C
   std::vector<int> C;
   for (int i=0; i<=k; i++)
   {
      C.push_back(0);
   }

   //C[i]包含等于i的元素个数
   for (int j=0; j<A.size(); j++)
   {
      C[A[j]] += 1;
   }

   //C[i]包含小于或等于i的元素个数
   for (int i=1; i<=k; i++)
   {
      C[i] += C[i-1]; 
   }

   for (int j=int(size(A))-1; j>=0; j--)
   {
      B[C[A[j]]-1] = A[j];
      C[A[j]] -= 1;
   }

   return B;
}