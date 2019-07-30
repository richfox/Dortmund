#pragma once

#include "basedef.h"
#include <string>



namespace XFU
{
   class TmpConfig sealed : public Object, private NonCopyable
   {
   public:
      static int load_tmp_setting(const std::wstring& node);
      static void save_tmp_setting(int setting,const std::wstring& node);

   private:
      static std::wstring _fname;
   };
}