//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "ObjectStringTest.h"
#include "..\Container\ObjectString.h"
#include "..\Container\StringUtil.h"
#include "..\LibraryManaged\LibraryManaged.h"

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
   CPPUNIT_ASSERT(string.CountOf(L't')==2);

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

   auto vec = string.Split(L't');
   std::vector<WOString> vectmp{L"",L"es",L"xfu"};
   CPPUNIT_ASSERT(vec == vectmp);
   vec = string.Split(L"st");
   vectmp = {L"te",L"xfu"};
   CPPUNIT_ASSERT(vec == vectmp);
   vec = string.Split(L"stt");
   vectmp = {string};
   CPPUNIT_ASSERT(vec == vectmp);
   vectmp = {string};
   string.Split(L"tttttttttttt");
   CPPUNIT_ASSERT(vec == vectmp);
   vectmp = {L"",L"estxfu"};
   vec = string.Split(L"t",1);
   CPPUNIT_ASSERT(vec == vectmp);
   vectmp = {L"",L"es",L"xfu"};
   vec = string.Split(L"t",2);
   CPPUNIT_ASSERT(vec == vectmp);
   vectmp = {L"",L"es",L"xfu"};
   vec = string.Split(L"t",3);
   CPPUNIT_ASSERT(vec == vectmp);
   vec = string.Split(L"t",2);
   CPPUNIT_ASSERT(vec.size() == string.CountOf(L"t") + 1);
   vec = string.Split(L"t",-3);
   CPPUNIT_ASSERT(vec.size() == string.CountOf(L"t") + 1);

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

   WOString string9 = L"test";
   CPPUNIT_ASSERT(string9.Reverse() == L"tset");
   string9 = L"te_st";
   CPPUNIT_ASSERT(string9.Reverse() == L"ts_et");

   int dis = edit_distance<wchar_t>(L"Sunday",L"Saturday",1,1,1);
   CPPUNIT_ASSERT(dis == 3);
   dis = edit_distance<wchar_t>(L"Sitting",L"Kitten",1,1,1);
   CPPUNIT_ASSERT(dis == 3);

   size_t close = -1;
   bool res = search_close_bracket(L"(((1+2)*3)-1)",0,close);
   CPPUNIT_ASSERT(res == true);
   CPPUNIT_ASSERT(close == 12);

   CPPUNIT_ASSERT(Managed::test_string_converter() == true);

   AOString string10 = ftoA(2.718281828459);
   CPPUNIT_ASSERT(string10 == "2.718281828459");
   WOString string11 = ftoW(3.14159265358979323846264338327950288419716939937510582097494459230781640628620899);
   CPPUNIT_ASSERT(string11 == L"3.141592653589793");

   WOString string12 = L"tesT";
   WOString string13 = L"TESt";
   WOString string14 = L"TESt2";
   CPPUNIT_ASSERT(string12.Compare(string13) > 0);
   CPPUNIT_ASSERT(string13.Compare(string12) < 0);
   CPPUNIT_ASSERT(string12 != string13);
   CPPUNIT_ASSERT(string13.Compare(string14) < 0);

   AOString string15 = "tesT";
   CPPUNIT_ASSERT(string15.Upper() == "TEST");
   WOString string16 = L"tesT";
   CPPUNIT_ASSERT(string16.Upper() == L"TEST");
   AOString string17 = "TESt";
   CPPUNIT_ASSERT(string17.Lower() == "test");
   WOString string18 = L"TESt";
   CPPUNIT_ASSERT(string18.Lower() == L"test");

   AOString str19 = "tesT";
   AOString str20 = "teSt";
   CPPUNIT_ASSERT(str19.ICompare(str20) == 0);
   CPPUNIT_ASSERT(str19 == "tesT");
   CPPUNIT_ASSERT(str20 == "teSt");

   WOString str21 = L"tesT";
   WOString str22 = L"teSt";
   CPPUNIT_ASSERT(str21.ICompare(str22) == 0);
   CPPUNIT_ASSERT(str21 == L"tesT");
   CPPUNIT_ASSERT(str22 == L"teSt");


   double tol = 0.000001;
   CPPUNIT_ASSERT(double_to_string(18,6) == L"18");
   CPPUNIT_ASSERT(double_to_string(10,6) == L"10");
   CPPUNIT_ASSERT(double_to_string(18.00000001,6) == L"18");
   CPPUNIT_ASSERT(double_to_string(17.99999999,6) == L"18");
   CPPUNIT_ASSERT(double_to_string(18.1234567,6) == L"18.123457");
   CPPUNIT_ASSERT(double_to_string(200000000,6) == L"2e+08");
   CPPUNIT_ASSERT(double_to_string(199999999,6) == L"2e+08");
   CPPUNIT_ASSERT(double_to_string(220000000,6) == L"2.2e+08");

   CPPUNIT_ASSERT(double_to_string(18,6,false) == L"18.000000");
   CPPUNIT_ASSERT(double_to_string(10,6,false) == L"10.000000");
   CPPUNIT_ASSERT(double_to_string(18.00000001,6,false) == L"18.000000");
   CPPUNIT_ASSERT(double_to_string(17.99999999,6,false) == L"18.000000");
   CPPUNIT_ASSERT(double_to_string(18.1234567,6,false) == L"18.123457");
   CPPUNIT_ASSERT(double_to_string(200000000,6,false) == L"2.000000e+08");
   CPPUNIT_ASSERT(double_to_string(199999999,6,false) == L"2.000000e+08");
   CPPUNIT_ASSERT(double_to_string(220000000,6,false) == L"2.200000e+08");

   CPPUNIT_ASSERT(fabs(string_to_double(L"1.8e2")-180) < tol);
   CPPUNIT_ASSERT(fabs(string_to_double(L"1.81234567e2")-181.234567) < tol);
}