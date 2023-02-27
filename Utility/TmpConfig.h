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

   private:
      static std::wstring _fname;
   };
}
