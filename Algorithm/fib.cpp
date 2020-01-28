#include "stdafx.h"
#include "fib.h"
#include <vector>


using namespace std;


int fibonacci(int n) //递归算法,O(2^n)
{
   if (n < 2)
	  return n;
   return fibonacci(n-1) + fibonacci(n-2);
}

int dynamic_fibonacci(int n) //动态规划算法,O(n)
{
   std::vector<int> res; //用于缓存以往结果
   res.reserve(n+1);

   for (int i=0; i<n+1; i++) //按顺序从小往大算
   {
      res.push_back(-1);
      if (i < 2)
         res[i] = i;
      else
         res[i] = res[i-1] + res[i-2]; //状态转移方程
   }

   return res[n];
}