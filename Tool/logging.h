#pragma once

#include <string>
#include <fstream>
#include <time.h>
#include <windows.h>

namespace XFU
{
   static void log_message(const std::wstring& file,const std::wstring& message)
   {
      std::wofstream ofs(file.c_str(),std::ios::app); //append to end of file
      if (ofs.is_open())
      {
         char tbuf[128] = "";
         char dbuf[128] = "";
         _strtime_s(tbuf,_countof(tbuf));
         _strdate_s(dbuf,_countof(dbuf));
         ofs << "[" << dbuf << ", " << tbuf << ", " << GetTickCount() << "] " << message << "\n";
         ofs.close();
      }
   }

   static void log_message_ex(const char* code,int line,const std::wstring& file,const std::wstring& message)
   {
      std::wofstream ofs(file.c_str(), std::ios::app); //append to end of file
      if (ofs.is_open())
      {
         char tbuf[128] = "";
         char dbuf[128] = "";
         _strtime_s(tbuf, _countof(tbuf));
         _strdate_s(dbuf, _countof(dbuf));
         ofs << "[" << dbuf << ", " << tbuf << ", " << GetTickCount() << "] [" << code << "," << line << "] " << message << "\n";
         ofs.close();
      }
   }
}