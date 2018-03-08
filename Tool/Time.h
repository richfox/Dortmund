#pragma once

#include <time.h>

namespace XFU
{
   // Calls the provided work function and returns the number of milliseconds
   // that it takes to call that function.
   template <class Function>
   __int64 time_call(Function&& f)
   {
      __int64 begin = GetTickCount();
      f();
      return GetTickCount() - begin;
   }

   //Start-Zeit definition, diese Zeit darf nie geändert werden!
   const static __time64_t utcStartTime = 1397058688; //Dortmund 9.4.2014 17:50

   //aktuelle UTC-Zeit als 32bit Integer umrechnen
   int current_utc_time_to_int32()
   {
      __time64_t t;
      _time64(&t);

      __time64_t diff = t - utcStartTime;

      return static_cast<int>(diff);
   }
}