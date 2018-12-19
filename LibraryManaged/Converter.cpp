#include "stdafx.h"
#include "Converter.h"
#include "LibraryManaged.h"

using namespace std;
using namespace XFU;
using namespace System;


template<typename T>
void DotNetTypeConverter<String^,ObjectString<T>>::ConvertToNative(const String^% in,ObjectString<T>& out)
{
   IntPtr ptr;
   if (typeid(T) == typeid(wchar_t))
      ptr = Runtime::InteropServices::Marshal::StringToHGlobalUni(const_cast<String^>(in));
   else if (typeid(T) == typeid(char))
      ptr = Runtime::InteropServices::Marshal::StringToHGlobalAnsi(const_cast<String^>(in));

   int length = const_cast<String^>(in)->Length;
   out = ObjectString<T>(reinterpret_cast<const T*>(ptr.ToPointer()),length);

   Runtime::InteropServices::Marshal::FreeHGlobal(ptr);
}

template<typename T>
void DotNetTypeConverter<String^,ObjectString<T>>::ConvertToManaged(const ObjectString<T>& in,String^% out)
{
   IntPtr ptr(const_cast<void*>(reinterpret_cast<const void*>(in.Buffer())));
   int length = static_cast<int>(in.Length());
   if (typeid(T) == typeid(wchar_t))
      out = Runtime::InteropServices::Marshal::PtrToStringUni(ptr,length);
   else if (typeid(T) == typeid(char))
      out = Runtime::InteropServices::Marshal::PtrToStringAnsi(ptr,length);

   //Runtime::InteropServices::Marshal::FreeHGlobal(ptr);
}

bool XFU::Managed::test_string_converter()
{
   const String^ in = "test";
   ObjectString<wchar_t> out;
   DotNetTypeConverter<String^,ObjectString<wchar_t>>::ConvertToNative(in,out);
   if (out != L"test")
      return false;

   AOString out2;
   DotNetTypeConverter<String^,ObjectString<char>>::ConvertToNative(in,out2);
   if (out2 != "test")
      return false;

   const WOString in2 = L"xfu";
   String^ out3;
   DotNetTypeConverter<String^,WOString>::ConvertToManaged(in2,out3);
   if (out3 != "xfu")
      return false;

   const AOString in3 = "xfutest";
   DotNetTypeConverter<String^,AOString>::ConvertToManaged(in3,out3);
   if (out3 != "xfutest")
      return false;

   return true;
}