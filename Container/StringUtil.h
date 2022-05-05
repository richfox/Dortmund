//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#pragma once

#include <string>
#include "ObjectString.h"


namespace XFU
{
   WOString __declspec(dllexport) i16toW(__int16 val);
   WOString __declspec(dllexport) i32toW(__int32 val);
   WOString __declspec(dllexport) i64toW(__int64 val);
   AOString __declspec(dllexport) ftoA(double val);
   WOString __declspec(dllexport) ftoW(double val);
   

   template<typename T>
   bool is_symmetrical(const ObjectString<T>& string)
   {
      const T* begin = string.Buffer();
      const T* end = string.Buffer() + string.Length() - 1;

      while (begin < end)
      {
         if (*begin != *end)
            return false;
         begin++;
         end--;
      }

      return true;
   }


   //edit distance between two strings
   int __declspec(dllexport) edit_distance(const std::wstring& lhs,const std::wstring& rhs,const int dcost,const int icost,const int scost);

   bool __declspec(dllexport) search_close_bracket(const std::wstring& str,const std::wstring::size_type& posOpen,std::wstring::size_type& posClose);
   std::wstring __declspec(dllexport) double_to_string(const double input,int precision=-1,bool ignorezero=true);
   double __declspec(dllexport) string_to_double(const std::wstring input);

   //longest Common Subsequence, O(mn)
   int __declspec(dllexport) lcs(const std::wstring x,const std::wstring y);
   //print longest Common Subsequence, O(m+n)
   void __declspec(dllexport) lcs_print(int** dp,const std::wstring x,const std::wstring y,int i,int j);
}