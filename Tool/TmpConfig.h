#pragma once

#include "basedef.h"
#include <string>



namespace XFU
{
   template<typename T>
   class TmpConfig sealed : public Object, private NonCopyable
   {
   public:
      static const T load_tmp_setting(const std::wstring& node);
      static void save_tmp_setting(const T& setting,const std::wstring& node);

   private:
      static std::wstring _fname;
   };
}

