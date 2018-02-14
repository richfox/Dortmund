//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "ObjectStringTest.h"
#include "..\Container\ObjectString.h"

using namespace std;
using namespace XFU;
//using namespace boost;


CPPUNIT_TEST_SUITE_REGISTRATION(ObjectStringTest);



void ObjectStringTest::test()
{
   WOString string(L"test",4);
   CPPUNIT_ASSERT(string.Length()==4);
   CPPUNIT_ASSERT(string[2]==L's');
   CPPUNIT_ASSERT(string.IndexOf(L't')==0);

   const auto t = string.Buffer();
   std::wstring ws(L"test");
   const auto t2 = ws.c_str();
   CPPUNIT_ASSERT(wcscmp(t,t2)==0);
   CPPUNIT_ASSERT(wcscmp(WOString(ws.c_str()).Buffer(),t2)==0);

   string = string;
   WOString tmp = string; 
   string = L"foo"; //assign to new string will delete the old,
			      //but the old still have reference at WOString tmp,
			      //this will cause error when dtor of WOString tmp is called, 
			      //so must set a ref. counter 

   string.Assign(L"");
   string.Assign(L"fff");
   string.Assign(tmp);
   WOString string2(L"x");
   string += string2;
   string.Append(WOString(L"f"));
   string.Append(L"u");
   CPPUNIT_ASSERT(string==L"testxfu");

   bool eq = (string == string2);
   eq = (string != string2);
   eq = (string == L"foo");
   eq = (L"foo" == string);
   eq = (L"foo"==L"foo");

   auto left = string.Left(2);
   CPPUNIT_ASSERT(left==L"te");
   auto right = string.Right(2);
   CPPUNIT_ASSERT(right==L"fu");
   auto substr = string.Substr(2,2);
   CPPUNIT_ASSERT(substr==L"st");
   substr = string.Substr(2);
   CPPUNIT_ASSERT(substr==L"stxfu");
   string.Substr(2,2).Buffer();

   auto pos = string.Find(L"t",0,1);
   CPPUNIT_ASSERT(pos==0);
   pos = string.Find(L"tx",0,2);
   CPPUNIT_ASSERT(pos==3);
   pos = string.Find(L"x",pos,1);
   pos = string.Find(WOString(L"xfu"));
   pos = string.Find(L"xfu",1);
   CPPUNIT_ASSERT(pos==4);
   pos = string.Find(L'x');

   pos = string.ReverseFind(L"t",string.Length(),1);
   CPPUNIT_ASSERT(pos==3);
   pos = string.ReverseFind(L"te",2,2);
   pos = string.ReverseFind(WOString(L"test"));
   pos = string.ReverseFind(L"test");
   pos = string.ReverseFind(L't');
   pos = string.ReverseFind(string);
   CPPUNIT_ASSERT(pos==0);
   pos = string.ReverseFind(string,string.Length()-1);
   CPPUNIT_ASSERT(pos==0);

   string.Insert(4,WOString(L"some",4)).Insert(4,WOString::_empty);
   CPPUNIT_ASSERT(string==L"testsomexfu");
   string.Remove(4,2).Remove(4,2);
   CPPUNIT_ASSERT(string==L"testxfu");
   string.Remove(string.Length(),0);
   CPPUNIT_ASSERT(string==L"testxfu");

   WOString string3(L"  tttt  ",8);
   string3.Trim(L' ').Trim(L't');
   CPPUNIT_ASSERT(string3==L"");
   CPPUNIT_ASSERT(WOString(L"  tttt   ").Trim(L' ')==L"tttt");

   std::wstring ws3 = string3.Buffer();
   WOString string4(ws3.c_str());
   string4.Empty();

   string4.Swap(string);
   CPPUNIT_ASSERT(string4 == L"testxfu");
   CPPUNIT_ASSERT(string == L"");
   string.Swap(string4);
	
   string.Replace(4,0,L"foo");
   string.Replace(4,3,WOString::_empty);
   CPPUNIT_ASSERT(string==L"testxfu");

   WOString string4_5 = L" test x f u ";
   string4_5.Replace(L" ",L"");
   CPPUNIT_ASSERT(string4_5==L"testxfu");
   string4_5 = L"test x f u";
   string4_5.Replace(L" ",L"");
   CPPUNIT_ASSERT(string4_5==L"testxfu");
   string4_5 = L"testtest";
   string4_5.Replace(L"test",L"test1");
   CPPUNIT_ASSERT(string4_5==L"test1test1");

   WOString string5 = WOString(L"test")+L"foo";
   CPPUNIT_ASSERT(string5 == L"testfoo");
   string5 = L"foo" + string5;
   CPPUNIT_ASSERT(string5 == L"footestfoo");
   string5 = string5 + string5;
   CPPUNIT_ASSERT(string5 == L"footestfoofootestfoo");

   AOString string6 = StringConverter<WOString,AOString>::Convert(string5);
   WOString string7 = StringConverter<AOString,WOString>::Convert(string6);
   CPPUNIT_ASSERT(string7 == string5);

   WOString string8 = L"testtset";
   CPPUNIT_ASSERT(is_symmetrical(string8)==true);
   string8 = L"test tset";
   CPPUNIT_ASSERT(is_symmetrical(string8)==true);
   string8 = L"test _tset";
   CPPUNIT_ASSERT(is_symmetrical(string8)==false);
}