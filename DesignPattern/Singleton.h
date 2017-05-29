#pragma once


#include "SingletonHolder.h"

namespace XFU
{
   template <typename T>
   inline T& get_T_singleton_pointer()
   {
      return Loki::SingletonHolder<T>::Instance();
   }

   template <typename T>
   struct CreateUsingStatic
   {
      static T& get_T_singleton()
      {
         static T t;
         return t;
      }
   };
}