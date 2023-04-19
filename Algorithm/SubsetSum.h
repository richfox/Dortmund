#pragma once

#include <iostream>
#include <vector>

static std::vector<int> sss;

bool isSubsetSum(const std::vector<int>& set, int n, int sum)
{
   // Base Cases
   if (sum == 0)
      return true;
   if (n == 0)
      return false;
 
   // If last element is greater than sum,
   // then ignore it
   if (set[n - 1] > sum)
      return isSubsetSum(set, n - 1, sum);
 
   /* else, check if sum can be obtained by any
   of the following:
   (a) including the last element
   (b) excluding the last element   */
   //return isSubsetSum(set, n - 1, sum) || isSubsetSum(set, n - 1, sum - set[n - 1]);

   bool res = false;

   if (isSubsetSum(set, n - 1, sum - set[n - 1]))
   {
      sss.push_back(set[n - 1]);
      res = true;
   }
   else if (isSubsetSum(set, n - 1, sum))
   {
      res = true;
   }

   return res;
}