//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################


#include "stdafx.h"
#include "LogisExprTest.h"
#include "..\Parser\LogisTokenizer.h"



using namespace std;
using namespace XFU;

CPPUNIT_TEST_SUITE_REGISTRATION(LogisExprTest);


void LogisExprTest::setUp()
{}

void LogisExprTest::tearDown()
{}


void LogisExprTest::test()
{
   vector<wstring> tokens;

   tokens = run_logis_tokenizer(L"%A(1)  ");
   tokens = run_logis_tokenizer(L"  ");
   tokens = run_logis_tokenizer(L"yt");
   tokens = run_logis_tokenizer(L"zhongtong6666 + YT8888");
   tokens = run_logis_tokenizer(L"%A(%T(%S(t)))");
   tokens = run_logis_tokenizer(L"%R(zhongtong6666 + YT(8888 + 5641)) + %A(JD0001-1-1)");
   tokens = run_logis_tokenizer(L"  %R ( zhongtong6666 +  YT(  8888  +  5641  )  ) + %A(JD0001-1-1)  ");
}