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


   template<typename T>
   int edit_distance(const ObjectString<T>& lhs,const ObjectString<T>& rhs,const int dcost,const int icost,const int scost)
   {
      //https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm

      int row = lhs.Length() + 1;
      int col = rhs.Length() + 1;

      std::vector<std::vector<int>> dist(row,std::vector<int>(col));
      for (int i=0; i<row; i++)
      {
         dist[i][0] = i * dcost;
      }
      for (int i=0; i<col; i++)
      {
         dist[0][i] = i * icost;
      }

      for (int i=1; i<col; i++)
      {
         for (int j=1; j<row; j++)
         {
            if (lhs[j-1] == rhs[i-1])
            {
               dist[j][i] = dist[j-1][i-1];
            }
            else
            {
               int deletion = dist[j-1][i] + dcost;
               int insertion = dist[j][i-1] + icost;
               int substitution = dist[j-1][i-1] + scost;
               dist[j][i] = min(min(deletion,insertion),substitution);
            }
         }
      }

      return dist[row-1][col-1];
   }

   bool __declspec(dllexport) search_close_bracket(const std::wstring& str,const std::wstring::size_type& posOpen,std::wstring::size_type& posClose);
   std::wstring __declspec(dllexport) double_to_string(const double input,int precision=-1,bool ignorezero=true);
   double __declspec(dllexport) string_to_double(const std::wstring input);
}