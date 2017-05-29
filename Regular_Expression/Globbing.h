#pragma once


#include <string>



namespace XFU
{
   std::wstring str_to_ecmascript_regex(const std::wstring& in);
   bool is_positive_and_null_integer(const std::wstring& in);
   bool is_positive_integer(const std::wstring& in);
}