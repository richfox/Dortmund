//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "StringUtil.h"
#include <stack>
#include <iostream>


using namespace std;
using namespace XFU;


WOString XFU::i16toW(__int16 val)
{
   wchar_t buffer[256];
   _itow_s(static_cast<int>(val),buffer,_countof(buffer),10);
   return buffer;
}

WOString XFU::i32toW(__int32 val)
{
   wchar_t buffer[256];
   _itow_s(val,buffer,_countof(buffer),10);
   return buffer;
}

WOString XFU::i64toW(__int64 val)
{
   wchar_t buffer[256];
   _i64tow_s(val,buffer,_countof(buffer),10);
   return buffer;
}


AOString XFU::ftoA(double val)
{
   char buffer[256];
   _gcvt_s(buffer,val,16);
   size_t len = strlen(buffer);
   if (buffer[len-1] == '.')
   {
	  buffer[len-1]='\0';
   }
   return buffer;
}

WOString XFU::ftoW(double val)
{
   return StringConverter<AOString,WOString>::Convert(XFU::ftoA(val));
}



bool XFU::search_close_bracket(const std::wstring& str,const std::wstring::size_type& posOpen,std::wstring::size_type& posClose)
{
   bool res = false;

   stack<wstring::size_type> opens;
   auto start = posOpen + 1;
   auto pos = str.find_first_of(L"()", start);
   while (pos != wstring::npos)
   {
      if (str.at(pos) == L'(')
      {
         opens.push(pos);
      }
      else if (str.at(pos) == L')')
      {
         if (opens.empty())
         {
            res = true;
            posClose = pos;
            break;
         }
         else
         {
            opens.pop();
         }
      }

      start = pos + 1;
      pos = str.find_first_of(L"()", start);
   }

   return res;
}


std::wstring XFU::double_to_string(const double input,int precision/*=-1*/,bool ignorezero/*=true*/)
{
   wstring res;
   wchar_t szOut[256];
   double tol = 1e-8;

   if (input > 99999999)
   {
      int iMod = 1;
      while (int(input) / iMod > 0)
      {
         iMod *= 10;
      }
      iMod /= 10;

      if (precision >= 0)
      {
         if (precision > 0 && ignorezero)
         {
            if (abs(input/iMod - int(input/iMod)) < tol || abs(input/iMod - int(input/iMod)) > 1-tol)
               precision = 0;
         }

         swprintf_s(szOut,L"%.*e",precision,input);
      }
      else
      {
         if (precision > 0 && ignorezero)
         {
            if (abs(input/iMod - int(input/iMod)) < tol || abs(input/iMod - int(input/iMod)) > 1-tol)
               precision = 0;
         }
         else
            precision = 8;

         swprintf_s(szOut,L"%.*e",precision,input);
      }

      //irrelevant Nachkommstelle wird ignoriert
      res.assign(szOut);
      if (precision > 0 && ignorezero)
      {
         wstring header = res.substr(0,res.find('e'));
         wstring tail = res.substr(res.find('e'));
         while (header[header.size()-1]=='0' || header[header.size()-1]=='.')
            header.resize(header.size()-1);
         res = header + tail;
      }
   }
   else
   {
      if (precision >= 0)
      {
         if (precision > 0 && ignorezero)
         {
            if (abs(input - int(input)) < tol || abs(input - int(input)) > 1-tol)
               precision = 0;
         }

         swprintf_s(szOut,L"%.*f",precision,input);
      }
      else
      {
         if (precision > 0 && ignorezero)
         {
            if (abs(input - int(input)) < tol || abs(input - int(input)) > 1-tol)
               precision = 0;
         }
         else
            precision = 8;

         swprintf_s(szOut,L"%.*f",precision,input);
      }

      res.assign(szOut);
      if (precision > 0 && ignorezero)
      {
         while (res[res.size()-1]=='0' || res[res.size()-1]=='.')
            res.resize(res.size()-1);
      }
   }

   return res;
}

double XFU::string_to_double(const std::wstring input)
{
   wchar_t* endptr = 0;
   double dvalue = wcstod(input.c_str(),&endptr);
   return dvalue;
}

int XFU::lcs(const std::wstring x,const std::wstring y)
{
   const int m = int(x.size()) + 1;
   const int n = int(y.size()) + 1;

   int** dp = new int*[m];
   for (int i=0; i<m; i++)
      dp[i] = new int[n];

   for (int i=0; i<m; i++)
      dp[i][0] = 0;
   for (int j=0; j<n; j++)
      dp[0][j] = 0;
   for (int i=1; i<m; i++)
      for (int j=1; j<n; j++)
         if (x.at(i-1) == y.at(j-1))
            dp[i][j] = dp[i-1][j-1] + 1;
         else
            if (dp[i-1][j] >= dp[i][j-1])
               dp[i][j] = dp[i-1][j];
            else
               dp[i][j] = dp[i][j-1];

   int res = dp[m-1][n-1];
   lcs_print(dp,x,y,m-1,n-1);

   for (int i=0; i<m; i++)
      delete[] dp[i];
   delete[] dp;

   return res;
}

void XFU::lcs_print(int** dp,const std::wstring x,const std::wstring y,int i,int j)
{
   if (i==0 || j==0)
      return;
   if (x.at(i-1) == y.at(j-1))
   {
      lcs_print(dp,x,y,i-1,j-1);
      std::wcout << x.at(i-1);
   }
   else
   {
      if (dp[i-1][j] >= dp[i][j-1])
         lcs_print(dp,x,y,i-1,j);
      else
         lcs_print(dp,x,y,i,j-1);
   }
}