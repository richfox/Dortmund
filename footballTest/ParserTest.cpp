//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################


#include "stdafx.h"
#include "ParserTest.h"
#include "..\Parser\CalcTokenizer.h"
#include "..\Parser\CalcParser.h"
#include "..\Parser\CalcVisitor.h"


using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);


void ParserTest::setUp()
{}

void ParserTest::tearDown()
{}


void ParserTest::test()
{
   vector<wstring> tokens;

   tokens = XFU::run_tokenizer(L"(11+22)*33");
   CPPUNIT_ASSERT(tokens.size() == 7);
   CPPUNIT_ASSERT(tokens[6] == L"33");
   CPPUNIT_ASSERT(XFU::test_parser(tokens)==true);
   CPPUNIT_ASSERT(XFU::run_visitor(XFU::run_parser(tokens)) == L"(11+22)*33");

   tokens = XFU::run_tokenizer(L"11+22*33");
   CPPUNIT_ASSERT(tokens.size() == 5);
   CPPUNIT_ASSERT(tokens[4] == L"33");
   CPPUNIT_ASSERT(XFU::test_parser(tokens)==true);
   CPPUNIT_ASSERT(XFU::run_visitor(XFU::run_parser(XFU::run_tokenizer(L"11+22*33"))) == L"11+22*33");

   tokens = XFU::run_tokenizer(L"  (11 + 22)*33  ");
   CPPUNIT_ASSERT(tokens.size() == 7);
   CPPUNIT_ASSERT(tokens[2] == L"+");

   tokens = XFU::run_tokenizer(L"11+22*");
   CPPUNIT_ASSERT(XFU::test_parser(tokens)==false);

   tokens = XFU::run_tokenizer(L"11+(22");
   CPPUNIT_ASSERT(XFU::test_parser(tokens)==false);

   tokens = XFU::run_tokenizer(L"11+(22)");
   CPPUNIT_ASSERT(XFU::test_parser(tokens)==true);
   CPPUNIT_ASSERT(XFU::run_visitor(XFU::run_parser(tokens))==L"11+(22)");

   tokens = XFU::run_tokenizer(L"11+(22+(33+44))");
   CPPUNIT_ASSERT(XFU::test_parser(tokens)==true);

   tokens = XFU::run_tokenizer(L"11+((22+33)+44)");
   CPPUNIT_ASSERT(XFU::test_parser(tokens)==true);

   tokens = XFU::run_tokenizer(L"11+((22+33)*44)");
   CPPUNIT_ASSERT(XFU::test_parser(tokens)==true);

   tokens = XFU::run_tokenizer(L"11+(22*((1+2*(2*((1+1)*2)))-1)/2)");
   CPPUNIT_ASSERT(XFU::test_parser(tokens)==true);

   tokens = XFU::run_tokenizer(L"((22)))");
   CPPUNIT_ASSERT(tokens.size() == 3);
   CPPUNIT_ASSERT(tokens[0] == L"(");
   CPPUNIT_ASSERT(tokens[1] == L"22");
   CPPUNIT_ASSERT(tokens[2] != L")))");
   CPPUNIT_ASSERT(XFU::test_parser(tokens)==true);
   CPPUNIT_ASSERT(XFU::run_visitor(XFU::run_parser(tokens))==L"(22)");
}