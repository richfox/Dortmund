#pragma once

#include <string>
#include "macro.h"
#include "..\Tool\basedef.h"


namespace XFU
{
   class UTIL_CLASS TmpConfig sealed : public Object, private NonCopyable
   {
   public:
      template<typename T>
      static const T load_tmp_setting(const std::wstring& node);

      template<typename T>
      static void save_tmp_setting(const T& setting,const std::wstring& node);

      template<typename T>
      static void edit_tmp_setting(const T& setting,const std::wstring& node);

      static bool has_tmp_setting(const std::wstring& node);

      static void erase_tmp_setting(const std::wstring& node);

      static size_t count_tmp_setting(const std::wstring& node);

      static void delete_tmp_setting();

   private:
      static std::wstring _fname;
      static std::wstring _path;
   };
}
