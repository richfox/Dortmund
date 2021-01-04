#pragma once

#include <string>



namespace XFU
{
   inline std::wstring create_hash_string(int size)
   {
      std::wstring res;
      res.resize(size);
      static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

      for (int i=0; i<size; ++i) 
      {
         res[i] = alphanum[rand() % (_countof(alphanum)-1)];
      }

      return res;
   }
}