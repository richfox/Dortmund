#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <xfunctional>

#include "sort.h"


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


void print_subset(int set[], std::string** rs,int row,int col)
{
   if (rs[row][col] == "u")
   {
      print_subset(set, rs, row - 1, col);
   }
   else
   {
      if (rs[row][col] == "x")
      {
         std::cout << std::endl;
         return;
      }
      else
      {
         std::cout << set[row-1] << ",";
         int c = atoi(rs[row][col].c_str());
         print_subset(set, rs, row - 1, c);
      }
   }
}

//solve the problem in Pseudo-polynomial time O(sum*n) use the Dynamic programming.
//So we will create a 2D array of size (arr.size() + 1) * (target + 1) of type boolean. 
//The state DP[i][j] will be true if there exists a subset of elements from A[0…i] with sum value = j
bool isSubsetSum(int set[], int n, int sum)
{
   // 2D array
   auto **dp = new bool*[n+1];
   for (int i=0; i <n+1; i++)
   {
      dp[i] = new bool[sum + 1];
      for (int j=0; j<sum+1; j++)
      {
         dp[i][j] = false;
      }
   }

   // additional 2D array to reconstruct a subset 
   // "x": init value
   // "u": depend on element one row upwards in same column
   // digit: hold current element and jump to last row and column with the digit
   std::string **rs = new std::string*[n+1];
   for (int i=0; i<n+1; i++)
   {
      rs[i] = new std::string[sum + 1];
      for (int j=0; j<sum+1; j++)
      {
         rs[i][j] = "x";
      }
   }
 
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
         {
            if (dp[i - 1][j])
            {
               rs[i][j] = "u";
               dp[i][j] = true;
            }
         }
         else
         {
            if (dp[i - 1][j - set[i - 1]])
            {
               rs[i][j] = std::to_string(j-set[i - 1]).c_str();
               dp[i][j] = true;
            }
            else if (dp[i - 1][j])
            {
               rs[i][j] = "u";
               dp[i][j] = true;
            }
         }
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

   std::cout <<"\n\\";
   for (int i=0; i<=sum; i++)
   {
      printf("%4d", i);
   }
   std::cout <<"\n";
   for (int i=0; i<=n; i++)
   {
      printf("%d",(i==0)?0:set[i-1]);
      for (int j=0; j<=sum; j++)
         printf("%4s", rs[i][j].c_str());
      std::cout <<"\n";
   }
 
   bool res = dp[n][sum];
   if (res)
   {
      print_subset(set, rs, n, sum);
   }

   // release array memory
   for(int i=0; i<n+1; i++)
      delete[] dp[i];
   delete[] dp;

   for(int i=0; i<n+1; i++)
      delete[] rs[i];
   delete[] rs;

   return res;
}


//brute force O(2^n * n), since there are 2^n subsets and, to check each subset we need to sum at most n elements
int exact_subset_sum(const std::vector<int>& set, int sum)
{
   int n = int(set.size());
   std::vector<int> L = { 0 };

   for (int i = 0; i < n; i++)
   {
      std::vector<int>L2 = L;
      std::transform(L.begin(), L.end(), L2.begin(), [&](const int& elem)
      {
         return elem + set[i];
      });

      L = merge(merge_sort(L), merge_sort(L2));

      std::vector<int>::iterator it = std::remove_if(L.begin(), L.end(), std::bind2nd(std::greater<int>(), sum));
      L.erase(it, L.end());
   }

   return L.back();
}


//Fully-polynomial time approximation O(n/ϵ * n), L contains no more than n/ϵ  elements, therefore the run-time is polynomial in n/ϵ
//here approximation parameter 0<ϵ<1, this agorithmus return within 1+ϵ multiple of the optimal solution
int approx_subset_sum(const std::vector<int>& set, int sum, double epsilon)
{
   return 0;
}