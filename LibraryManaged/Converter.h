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


   //Alias template
   template<typename T>
   using stdstr = std::basic_string<T,std::char_traits<T>,std::allocator<T>>;

   template<typename T>
   struct DotNetTypeConverter<System::String^,stdstr<T>>
   {
      static void ConvertToNative(const System::String^% in,stdstr<T>& out);
      static void ConvertToManaged(const stdstr<T>& in,System::String^% out);
   };


   template<typename T>
   struct DotNetTypeConverter<System::String^,ObjectString<T>>
   {
      static void ConvertToNative(const System::String^% in,ObjectString<T>& out);
      static void ConvertToManaged(const ObjectString<T>& in,System::String^% out);
   };
}


