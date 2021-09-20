//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "StringUtil.h"
#include <stack>


using namespace std;
using namespace XFU;



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