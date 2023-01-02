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
         res[i] = res[i-1] + res[i-2]; //递推关系
   }

   return res[n];
}

int iterative_fibonacci(int n) //迭代算法,O(n)
{
   if (n == 0)
      return 0;
   else
   {
      int x = 0;
      int y = 1;
      for (int i=1; i<n; i++)
      {
         int z = x + y;
         x = y;
         y = z;
      }
      return y;
   }
}

void multiply(int F[2][2], int M[2][2])
{
    int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
     
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}
 
void power(int F[2][2], int n)
{
    int i;
    int M[2][2] = { { 1, 1 }, { 1, 0 } };
    for(i=2; i<=n; i++)
        multiply(F, M);
}

int matrix_fibonacci(int n) //Matrix幂算法，O(lgn)
{
   int F[2][2] = { { 1, 1 }, { 1, 0 } };
     
   if (n == 0)
      return 0;

   power(F, n-1);
        
   return F[0][0];
}

int formula_fibonacci(int n) //通项公式算法，O(lgn)
{
   double res = (1 + sqrt(5)) / 2;
   return round(pow(res,n) / sqrt(5));
}