#pragma once

#include <string>
#include <fstream>
#include <time.h>

namespace XFU
{
   void log_message(const std::wstring& file,const std::wstring& message)
   {
      std::wofstream ofs(file.c_str(),std::ios::app); //append to end of file
      __time64_t utc;
      _time64(&utc);
      char tbuf[128] = "";
      char dbuf[128] = "";
      _strtime_s(tbuf,_countof(tbuf));
      _strdate_s(dbuf,_countof(dbuf));
      ofs << "[" << dbuf << ", " << tbuf << ", " << utc << "] " << message << "\n";
      ofs.close();
   }
}