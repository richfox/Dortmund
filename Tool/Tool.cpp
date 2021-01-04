// Cache.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Cache.h"
#include "Guard.h"
#include "Debug.h"
#include "meta.h"
#include "Factorial.h"
#include "path.h"
#include "RegexUtil.h"
#include "Operation.h"
#include "Invoker.h"
#include "TmpConfig.h"
#include "Hash.h"
#include <conio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <regex>




using namespace std;
using namespace XFU;


int add(int a,int b)
{
   return a + b;
};

class Add
{
public:
   int add(int a,int b)
   {
      return a + b;
   }

   int operator()(int a,int b)
   {
      return a + b;
   }

   static int add2(int a,int b)
   {
      return a + b;
   }
};

class Foo
{
public:
   Foo()
      :_fInvoker(add),
      _sum(0)
   {
      _sum += _fInvoker(1,2);
   }

   int Sum()
   {
      return _sum;
   }

private:
   FreeInvoker<int,int,int> _fInvoker;
   int _sum;
};

int do_it_once()
{
   static Foo ito;
   return ito.Sum();
}

template<typename T>
class Foo2
{
public:
   Foo2(const T& value,const wstring& key)
      :_fInvoker(TmpConfig<T>::save_tmp_setting)
   {
      _fInvoker(value,key);
   }

private:
   FreeInvoker<void,const T&,const wstring&> _fInvoker;
};

void do_it_once2()
{
   static Foo2<wstring> foo2(L"xfu",L"config.wstring");
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



   //test Factorial
   CHECK_ERROR(XFU::Factorial<5>::value==XFU::fac(5),L"error");

   //test Path
   wstring current = XFU::XFUPath::GetCurrentPath();
   wstring currentparent = tr2::sys::path(current).parent_path();
   CHECK_ERROR(XFU::XFUPath::GetModulePath()== currentparent + L"\\..\\install\\",L"error");
   CHECK_ERROR(XFU::XFUPath::GetSystemTempPath()==L"C:\\Users\\xfu\\AppData\\Local\\Temp\\xfu\\",L"error");
   
   wstring roaming = XFU::XFUPath::GetRoamingPath();
   CHECK_ERROR(roaming==L"C:\\Users\\xfu\\AppData\\Roaming\\xfu\\",L"error");
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
   CHECK_ERROR(XFUPath::FindFileInPath(currentPath,L"Tool.cpp")==true,L"error");


   //test regex
   CHECK_ERROR(is_positive_and_null_float(L"34")==true,L"error");
   CHECK_ERROR(is_positive_and_null_float(L"34.")==false,L"error");
   CHECK_ERROR(is_positive_and_null_float(L"34.66")==true,L"error");
   CHECK_ERROR(is_positive_and_null_float(L"r34.66")==false,L"error");
   
   wstring testexpress = L"<Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists(\'$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\')\" Label=\"LocalAppDataPlatform\" />";
   wregex wre = wregex(str_to_ecmascript_regex(L"$(UserRootDir)\\Microsoft"));
   CHECK_ERROR(regex_search(testexpress,wre)==true,L"error");
   CHECK_ERROR(testexpress.length()-regex_replace(testexpress,wre,L"").length()==wstring(L"$(UserRootDir)\\Microsoft").length()*2,L"error");

   //test for with index
   int idx = 0;
   std::vector<int> testv(2,6);
   FOR_EACH(testv,it,ii)
   {
      if (idx == 0)
      {
         CHECK_ERROR(ii==0,L"error");
         CHECK_ERROR(*it==6,L"error");
      }
      idx++;
   }
   CHECK_ERROR(idx==2,L"error");

   //test variadic
   int a=0,b=0,c=0;
   double d = 1.1;
   std::wstring e = L"test";
   auto t = NUMARGS(a,b,c,d,e);

   //test invoker
   FreeInvoker<int,int,int> fInvoker(add);
   CHECK_ERROR(fInvoker.Invoke(1,2)==3,L"FreeInvoker error");
   CHECK_ERROR(fInvoker(1,2)==3,L"FreeInvoker error");
   FreeInvoker<int,int,int> fInvoker2(Add::add2);
   CHECK_ERROR(fInvoker2.Invoke(1,2)==3,L"FreeInvoker error");
   CHECK_ERROR(fInvoker2(1,2)==3,L"FreeInvoker error");

   Add madd;
   MemberInvoker<Add,int,int,int> mInvoker(&madd,&Add::add);
   CHECK_ERROR(mInvoker.Invoke(1,2)==3,L"MemberInvoker error");
   CHECK_ERROR(mInvoker(1,2)==3,L"MemberInvoker error");
   MemberInvoker<Add,int,int,int> mInvoker2(&madd,&Add::operator());
   CHECK_ERROR(mInvoker2.Invoke(1,2)==3,L"MemberInvoker error");
   CHECK_ERROR(mInvoker2(1,2)==3,L"MemberInvoker error");
   

   for (int i=0; i<10; i++)
   {
      CHECK_ERROR(do_it_once()==3,L"DoItOnce error");
   }

   //test temp config
   TmpConfig<int>::save_tmp_setting(1,L"config.int");
   CHECK_ERROR(TmpConfig<int>::load_tmp_setting(L"config.int")==1,L"config error");
   TmpConfig<int>::save_tmp_setting(2,L"config.int");
   CHECK_ERROR(TmpConfig<int>::load_tmp_setting(L"config.int")==2,L"config error");

   for (int i=0; i<10; i++)
   {
      do_it_once2();
   }
   CHECK_ERROR(TmpConfig<wstring>::load_tmp_setting(L"config.wstring")==L"xfu",L"config error");


   //test hash
   wstring hname;
   do
   {
      hname = create_hash_string(6);
      hname += L".xfu";
   } while(_waccess((XFUPath::GetSystemTempPath()+hname).c_str(),0) == 0);
   HANDLE hFile = CreateFileW ((XFUPath::GetSystemTempPath()+hname).c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
   CloseHandle(hFile);

   return 0;
}

