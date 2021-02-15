#pragma once

#include <vector>


//冒泡排序，O(n^2)
std::vector<int> bubble_sort(std::vector<int>& L)
{
   if (L.size() == 1)
      return L;
   
   for (std::size_t i=1; i<=L.size()-1; i++)
   {
      for (std::size_t j=1; j<=L.size()-i; j++)
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

//快速排序，O(nlogn)

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
