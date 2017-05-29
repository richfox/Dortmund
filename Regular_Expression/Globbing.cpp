
#include "stdafx.h"
#include <regex>
#include <stdint.h>
#include <atlstr.h>
#include "Globbing.h"


using namespace std;


wstring XFU::str_to_ecmascript_regex(const wstring& in)
{
   CString expr = in.c_str();

   //In ECMAScript regular expressions, all characters match themselves except for the following special characters.
   wstring spec[] = {L"\\",L"(",L")",L"{",L".",L"[",L"^",L"$",L"+",L"|",L"\"",L"/"};

   for_each(spec,spec+_countof(spec),[&](const wstring& elem)
   {
      //Any special character preceded by an escape shall match itself.
      expr.Replace(elem.c_str(),(L"\\"+elem).c_str());
   });

   expr.Replace(L"?",L".?");
   expr.Replace(L"*",L".*");

   return expr.GetBuffer();
}

bool XFU::is_positive_and_null_integer(const std::wstring& in)
{
   bool res = false;

   wregex rx(L"^[0-9]+$");
   res = regex_search(in,rx);
   if (res)
   {
      int iin = _wtoi(in.c_str());
      if (iin > INT32_MAX)
         res = false;
   }

   return res;
}

bool XFU::is_positive_integer(const std::wstring& in)
{
   bool res = false;

   wregex rx(L"^[0-9]+$");
   res = regex_search(in,rx);
   if (res)
   {
      int iin = _wtoi(in.c_str());
      if (iin==0 || iin>INT32_MAX)
         res = false;
   }

   return res;
}