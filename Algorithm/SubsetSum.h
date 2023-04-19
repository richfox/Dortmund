#pragma once

#include <iostream>
#include <vector>

static std::vector<int> sss; //hold the found subset

//This recursive solution may try all subsets of given set in worst case. Therefore time complexity is exponential.
//The problem is in-fact NP-Complete (nondeterministic polynomial time solution for this problem).
bool isSubsetSum(const std::vector<int>& set, int n, int sum)
{
   // Base Cases
   if (sum == 0)
      return true;
   if (n == 0)
      return false;
 
   // If last element is greater than sum, then ignore it
   if (set[n - 1] > sum)
      return isSubsetSum(set, n - 1, sum);
 
   /* else, check if sum can be obtained by any of the following:
   (a) including the last element isSubsetSum(set, n - 1, sum - set[n - 1])
   (b) excluding the last element isSubsetSum(set, n - 1, sum)  */

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