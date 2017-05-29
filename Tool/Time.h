#pragma once


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
}