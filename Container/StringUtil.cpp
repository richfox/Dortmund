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