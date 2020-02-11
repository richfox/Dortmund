//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################


#include "stdafx.h"
#include "LogisExprTest.h"
#include "..\Parser\LogisTokenizer.h"
#include "..\Parser\LogisParser.h"
#include "..\Parser\LogisVisitor.h"



using namespace std;
using namespace logis;

CPPUNIT_TEST_SUITE_REGISTRATION(LogisExprTest);


void LogisExprTest::setUp()
{}

void LogisExprTest::tearDown()
{}


void LogisExprTest::test()
{
   vector<wstring> tokens;

   tokens = run_logis_tokenizer(L"  ");
   CPPUNIT_ASSERT(tokens.empty());

   tokens = run_logis_tokenizer(L"%A(1)");
   CPPUNIT_ASSERT(tokens.size() == 4);
   CPPUNIT_ASSERT(tokens[3] == L")");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   CPPUNIT_ASSERT(run_logis_visitor(run_logis_parser(tokens)) == L"%A(1)");

   tokens = run_logis_tokenizer(L"yt");
   CPPUNIT_ASSERT(tokens.size() == 1);
   CPPUNIT_ASSERT(tokens[0] == L"yt");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   CPPUNIT_ASSERT(run_logis_visitor(run_logis_parser(tokens)) == L"yt");

   tokens = run_logis_tokenizer(L"(yt)");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   CPPUNIT_ASSERT(run_logis_visitor(run_logis_parser(tokens)) == L"(yt)");

   tokens = run_logis_tokenizer(L"zhongtong6666 + YT8888");
   CPPUNIT_ASSERT(tokens.size() == 3);
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   CPPUNIT_ASSERT(run_logis_visitor(run_logis_parser(tokens)) == L"zhongtong6666+YT8888");

   tokens = run_logis_tokenizer(L"%R(zhongtong6666) + %A(YT8888)");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   CPPUNIT_ASSERT(run_logis_visitor(run_logis_parser(tokens)) == L"%R(zhongtong6666)+%A(YT8888)");

   tokens = run_logis_tokenizer(L"%A(%T(%S(t + B)))");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   CPPUNIT_ASSERT(run_logis_visitor(run_logis_parser(tokens)) == L"%A(%T(%S(t+B)))");

   tokens = run_logis_tokenizer(L"%A(%T(%S(t)+ B))");
   auto s = tokens.size();
   CPPUNIT_ASSERT(tokens[s-1] == L")");
   CPPUNIT_ASSERT(tokens[s-2] == L")");
   CPPUNIT_ASSERT(tokens[s-3] == L"B");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   CPPUNIT_ASSERT(run_logis_visitor(run_logis_parser(tokens)) == L"%A(%T(%S(t)+B))");

   tokens = run_logis_tokenizer(L"(%A(%T(%S(t)))+ B)");
   CPPUNIT_ASSERT(tokens[0] == L"(");
   CPPUNIT_ASSERT(tokens[1] == L"%A");
   CPPUNIT_ASSERT(tokens[2] == L"(");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   CPPUNIT_ASSERT(run_logis_visitor(run_logis_parser(tokens)) == L"(%A(%T(%S(t)))+B)");

   tokens = run_logis_tokenizer(L"%A(%T(%S(t)))+ B");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   CPPUNIT_ASSERT(run_logis_visitor(run_logis_parser(tokens)) == L"%A(%T(%S(t)))+B");

   tokens = run_logis_tokenizer(L"%R(zhongtong6666 + YT(8888 + 5641)) + %A(JD0001-1-1)");
   CPPUNIT_ASSERT(tokens.size() == 16);
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);

   auto tokens2 = run_logis_tokenizer(L"  %R ( zhongtong6666 +  YT(  8888  +  5641  )  ) + %A(JD0001-1-1)  ");
   CPPUNIT_ASSERT(tokens.size() == 16);
   CPPUNIT_ASSERT(tokens == tokens2);
}