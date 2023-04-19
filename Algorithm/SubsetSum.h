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


//solve the problem in Pseudo-polynomial time O(sum*n) use the Dynamic programming.
//So we will create a 2D array of size (arr.size() + 1) * (target + 1) of type boolean. 
//The state DP[i][j] will be true if there exists a subset of elements from A[0…i] with sum value = j
bool isSubsetSum(int set[], int n, int sum)
{
   // 2D array
   auto **dp = new bool*[n+1];
   for(int i=0; i<n+1; i++)
      dp[i] = new bool[sum+1];
 
   // If sum is 0, then answer is true
   for (int i=0; i<=n; i++)
      dp[i][0] = true;
 
   // If sum is not 0 and set is empty,
   // then answer is false
   for (int i=1; i<=sum; i++)
      dp[0][i] = false;
 
   // Fill the dp table in bottom up manner
   for (int i=1; i<=n; i++)
   {
      for (int j=1; j<=sum; j++)
      {
         if (set[i - 1] > j)
            dp[i][j] = dp[i - 1][j];
         else
            dp[i][j] = dp[i - 1][j] || dp[i - 1][j - set[i - 1]];
      }
   }
 
   // print table
   std::cout <<"\\";
   for (int i=0; i<=sum; i++)
   {
      printf("%4d", i);
   }
   std::cout <<"\n";
   for (int i=0; i<=n; i++)
   {
      printf("%d",(i==0)?0:set[i-1]);
      for (int j=0; j<=sum; j++)
         printf("%4d", dp[i][j]);
      std::cout <<"\n";
   }
 
   bool res = dp[n][sum];

   for(int i=0; i<n+1; i++)
      delete[] dp[i];
   delete[] dp;

   return res;
}