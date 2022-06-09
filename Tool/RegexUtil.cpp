
#include "stdafx.h"
#include <regex>
#include <stdint.h>
#include <atlstr.h>
#include "RegexUtil.h"


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

bool XFU::is_positive_and_null_float(const std::wstring& in)
{
   bool res = false;

   wregex rx(L"^[0-9]+([.]{1}[0-9]+){0,1}$");
   res = regex_search(in,rx);
   if (res)
   {
      wchar_t* endptr = nullptr;
      double iin = wcstod(in.c_str(),&endptr);
      if (iin > DBL_MAX)
         res = false;
   }

   return res;
}

int XFU::extract_unsigned_integer(const std::wstring& in)
{
   int res = -1;

   wregex rx(L".*([0-9]+).*");
   std::wsmatch m;
   if (regex_match(in,m,rx))
   {
      if (m.size() == 2)
      {
         wstring val = m[1].str();
         res = std::stoi(val);
      }
   }

   return res;
}

float XFU::extract_unsigned_float(const std::wstring& in)
{
   float res = -1;

   wregex rx(L".*([0-9]+[.]{1}[0-9]+).*");
   std::wsmatch m;
   if (regex_match(in,m,rx))
   {
      if (m.size() == 2)
      {
         wstring val = m[1].str();
         res = std::stof(val);
      }
   }

   return res;
}