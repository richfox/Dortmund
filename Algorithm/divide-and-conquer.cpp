#include "stdafx.h"
#include "divide-and-conquer.h"
#include <iterator>
#include <algorithm>

using namespace std;



int find_cross_largest_sum(const std::vector<int>& seq)
{
   size_t mid = seq.size() / 2;

   //设最大和为0
   int llargest = 0;
   int rlargest = 0;

   int sum = 0;
   for (int i=mid-1; i>=0; i--)
   {
      sum += seq[i];
      if (sum > llargest)
      {
         llargest = sum;
      }
   }

   sum = 0;
   for (int i=mid; i<=seq.size()-1; i++)
   {
      sum += seq[i];
      if (sum > rlargest)
      {
         rlargest = sum;
      }
   }

   return llargest + rlargest;
}


int find_largest_sum(const std::vector<int>& seq)
{
   if (seq.size() == 1)
   {
      return seq[0]>0 ? seq[0] : 0;
   }

   size_t mid = seq.size() / 2;

   std::vector<int> lseq;
   lseq.reserve(mid);
   std::copy(seq.begin(),seq.begin()+mid,std::back_inserter(lseq));
   std::vector<int> rseq;
   rseq.reserve(mid);
   std::copy(seq.begin()+mid,seq.end(),std::back_inserter(rseq));

   int llargest = find_largest_sum(lseq);
   int rlargest = find_largest_sum(rseq);
   int clargest = find_cross_largest_sum(seq);

   if (llargest>=rlargest && llargest>=clargest)
   {
      return llargest;
   }
   else if (rlargest>=llargest && rlargest>=clargest)
   {
      return rlargest;
   }
   else
   {
      return clargest;
   }
}




int brute_force_find_largest_sum(const std::vector<int>& seq)
{
   if (seq.size() == 1)
   {
      return seq[0]>0 ? seq[0] : 0;
   }

   //设最大和为0
   int largest = 0;

   int sum = 0;
   for (int i=0; i<=seq.size()-1; i++)
   {
      sum = seq[i];
      for (int j=i+1; j<=seq.size()-1; j++)
      {
         sum += seq[j];
         if (sum > largest)
         {
            largest = sum;
         }
      }
   }

   return largest;
}