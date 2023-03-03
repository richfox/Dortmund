#include "stdafx.h"
#include "TmpConfigTest.h"
#include "..\Tool\Invoker.h"
#include "..\Utility\TmpConfig.h"


using namespace std;
using namespace XFU;

CPPUNIT_TEST_SUITE_REGISTRATION(TmpConfigTest);


template<typename T>
class Foo2
{
public:
   Foo2(const T& value,const wstring& key)
      :_fInvoker(TmpConfig::save_tmp_setting)
   {
      _fInvoker(value,key);
   }

private:
   FreeInvoker<void,const T&,const wstring&> _fInvoker;
};

void do_it_once()
{
   static Foo2<wstring> foo2(L"xfu",L"config.wstring");
}

void TmpConfigTest::test()
{
   cout << "\r\ntest temp config using property_tree...\r\n" << endl;

   TmpConfig::delete_tmp_setting();

   TmpConfig::save_tmp_setting<int>(1,L"config.int");
   CPPUNIT_ASSERT(TmpConfig::load_tmp_setting<int>(L"config.int")==1,L"config error");
   TmpConfig::save_tmp_setting<int>(2,L"config.int");
   CPPUNIT_ASSERT(TmpConfig::load_tmp_setting<int>(L"config.int")==1,L"config error");
   TmpConfig::edit_tmp_setting<int>(3,L"config.int");
   CPPUNIT_ASSERT(TmpConfig::load_tmp_setting<int>(L"config.int")==3,L"config error");

   CPPUNIT_ASSERT(TmpConfig::has_tmp_setting(L"config.int")==true,L"config error");
   CPPUNIT_ASSERT(TmpConfig::has_tmp_setting(L"config.double")==false,L"config error");

   CPPUNIT_ASSERT(TmpConfig::count_tmp_setting(L"config.int")==2,L"config error");
   TmpConfig::erase_tmp_setting(L"config.int");
   CPPUNIT_ASSERT(TmpConfig::count_tmp_setting(L"config.int")==0,L"config error");
   
   for (int i=0; i<10; i++)
   {
      do_it_once();
   }
   CPPUNIT_ASSERT(TmpConfig::count_tmp_setting(L"config.wstring")==1,L"config error");
   CPPUNIT_ASSERT(TmpConfig::load_tmp_setting<wstring>(L"config.wstring")==L"xfu",L"config error");

   TmpConfig::delete_tmp_setting();
}