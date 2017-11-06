﻿// Cache.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Cache.h"
#include "Guard.h"
#include "Debug.h"
#include "meta.h"
#include "Factorial.h"
#include "path.h"
#include <conio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>






using namespace std;
using namespace XFU;



int globaltemp = 0;

const int get_temp()
{
   return globaltemp;
}

void set_temp(const int& t)
{
   globaltemp = t;
}






int _tmain(int argc, _TCHAR* argv[])
{
   //test Cache
   map<wstring,wstring> mapping;
   mapping.insert(make_pair(L"D1",L"D2"));
   mapping.insert(make_pair(L"D11",L"D12"));
   CHECK_ERROR(get_cache(mapping).Cleared()==false,L"test_cache(): error");

   get_cache(mapping).ClearCache();
   CHECK_ERROR(get_cache(mapping).Cleared()==true,L"test_cache(): error");

   mapping.insert(make_pair(L"D3",L"D4"));
   get_cache(mapping).UpdateCache(mapping);
   CHECK_ERROR(get_cache(mapping).Cleared()==false,L"test_cache(): error");

   auto& it = get_cache(mapping).Cached()->find(L"D11");
   CHECK_ERROR(it->second==L"D12",L"test_cache(): error");

   //同样的类型只产生一个实例
   map<wstring,wstring> tempmap;
   get_cache(tempmap).ClearCache();
   CHECK_ERROR(get_cache(mapping).Cleared()==true,L"test_cache(): error");

   int temp = 100;
   CHECK_ERROR(get_cache(temp).Cleared()==false,L"test_cache(): error");

   _CLEAR_CACHE_TYPE_(std::map<int _ int>);
   std::map<int,int> ttt;
   CHECK_ERROR(get_cache(ttt).Cleared()==true,L"error");
   CHECK_ERROR(get_cache(ttt).Cached()==nullptr,L"error");

   if (!get_cache(ttt).Cleared())
   {
      get_cache(ttt).Cached()->insert(make_pair(1,2));
   }
   else
   {
      ttt.insert(make_pair(1,2));
      _UPDATE_CACHE_(std::map<int _ int>,ttt);
   }

   CHECK_ERROR(get_cache(ttt).Cleared()==false,L"error");
   CHECK_ERROR(get_cache(ttt).Cached()!=nullptr,L"error");
   CHECK_ERROR(get_cache(ttt).Cached()->find(1)!=get_cache(ttt).Cached()->end(),L"error");
   CHECK_ERROR(get_cache(ttt).Cached()->find(10)==get_cache(ttt).Cached()->end(),L"error");

   (*get_cache(ttt).Cached())[1] = 20;
   get_cache(ttt).Cached()->insert(make_pair(2,3));
   CHECK_ERROR(get_cache(ttt).Cached()->find(1)->second==20,L"error");
   CHECK_ERROR(get_cache(ttt).Cached()->find(2)->second==3,L"error");

   //test Guard
   XFU::Guard<int> guard([&]()->int
   {
      return globaltemp;
   },[&](const int& t)
   {
      globaltemp = t;
   });

   globaltemp = 1;

   std::unique_ptr<XFU::Guard<int>> guardheap(new XFU::Guard<int>(get_temp,set_temp));

   globaltemp = 2;

   //test Factorial
   CHECK_ERROR(XFU::Factorial<5>::value==XFU::fac(5),L"error");

   //test Path
   CHECK_ERROR(XFU::XFUPath::GetModulePath()==L"D:\\xfu_studio_files\\new_test_at_dortmund",L"error");
   CHECK_ERROR(XFU::XFUPath::GetSystemTempPath()==L"C:\\Users\\XFU~1.INT\\AppData\\Local\\Temp\\xfu",L"error");
   
   wstring roaming = XFU::XFUPath::GetRoamingPath();
   CHECK_ERROR(roaming==L"C:\\Users\\xfu.INTL\\AppData\\Roaming\\xfu",L"error");
   if (XFUPath::Exist(roaming))
   {
      XFUPath::Delete(roaming);
      CHECK_ERROR(XFUPath::Exist(roaming)==false,L"error");
   }
   else
   {
      XFUPath::Create(roaming);
      CHECK_ERROR(XFUPath::Exist(roaming)==true,L"error");
   }

   wchar_t currentPath[MAX_PATH];
   _wgetcwd(currentPath,_countof(currentPath));
   CHECK_ERROR(XFUPath::FindFileInPath(currentPath,L"Tool.exe")==false,L"error");
   CHECK_ERROR(XFUPath::FindFileInPath(currentPath,L"Tool.obj")==true,L"error");

   return 0;
}
