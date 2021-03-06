﻿#pragma once



#include <functional>


namespace XFU
{
   //模板元编程
   template<unsigned int n>
   struct Factorial
   {
      enum
      {
         value = n * Factorial<n-1>::value
      };
   };

   template<>
   struct Factorial<0>
   {
      enum
      {
         value = 1
      };
   };

   //函数式
   std::function<int(int)> fac = [&](int x)->int
   {
      return x<1 ? 1 : x*fac(x-1);
   };

   //递归函数
   int factorial(int n)
   {
      if (n == 0)
         return 1;
      else
         return n * factorial(n-1);
   }
}