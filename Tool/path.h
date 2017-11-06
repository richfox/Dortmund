//########################################################
//##                                                    ##
//##        Copyright: www.zhongwenshu.de               ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################
#pragma once


#include <string>
#include <filesystem>
#include <windows.h>
#include <stdlib.h>
#include <filesystem>
#include "basedef.h"
#include "Error.h"



namespace XFU
{
   namespace fs = std::tr2::sys;

   class XFUPath : public Object
   {
   public:
      static bool Exist(const std::wstring& path)
      {
         return _waccess(path.c_str(),0) == 0;
      }

      static bool Create(const std::wstring& path)
      {
         return _wmkdir(path.c_str()) == 0;
      }

      static bool Delete(const std::wstring& path)
      {
         return _wrmdir(path.c_str()) == 0;
      }



      static const std::wstring GetModulePath()
      {
         wchar_t buffer[MAX_PATH];
         GetModuleFileNameW(nullptr,buffer,sizeof(buffer)); //D:\xfu_studio_files\new_test_at_dortmund\x64\Debug\Tool.exe

         return std::tr2::sys::wpath(buffer).parent_path().parent_path().parent_path(); //D:\xfu_studio_files\new_test_at_dortmund
      }

      static const std::wstring GetSystemTempPath()
      {
         wchar_t buffer[MAX_PATH];

         DWORD retval = GetTempPathW(_countof(buffer),buffer);
         if (retval==0 || retval>_countof(buffer))
            throw Error(L"GetTempPath failed");

         return std::wstring(buffer) + L"xfu"; //C:\Users\xfu.INTL\AppData\Local\Temp\xfu
      }

      static const std::wstring GetRoamingPath()
      {
         wchar_t buffer[MAX_PATH];
         size_t requiredSize = 0;  
  
         _wgetenv_s(&requiredSize,buffer,_countof(buffer),L"APPDATA");  

         return std::wstring(buffer) + L"\\xfu"; //C:\Users\xfu.INTL\AppData\Roaming\xfu
      }

      static bool FindFileInPath(const std::wstring& path,const std::wstring& file)
      {
         fs::wpath mainpath(path.c_str());
         fs::wdirectory_iterator it(mainpath);
         fs::wdirectory_iterator endit;
         for (; it!=endit; it++)
         {
            if (fs::is_directory(it->status()))
            {
               if (FindFileInPath(it->path(),file))
                  return true;
            }
            else if (fs::is_regular_file(it->status()))
            {
               if (!_wcsicmp(it->path().filename().c_str(),file.c_str()))
                  return true;
            }
         }

         return false;
      }
   };
}