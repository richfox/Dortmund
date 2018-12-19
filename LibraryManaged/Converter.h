#pragma once

#include <string>
#include "..\Container\ObjectString.h"

namespace XFU
{
   template<typename M,typename N>
   struct DotNetTypeConverter
   {
      static void ConvertToNative(const M% managed,N& native);
      static void ConvertToManaged(const N& native,M% managed);
   };


   template<typename T>
   struct DotNetTypeConverter<System::String^,ObjectString<T>>
   {
      static void ConvertToNative(const System::String^% in,ObjectString<T>& out);
      static void ConvertToManaged(const ObjectString<T>& in,System::String^% out);
   };
}


