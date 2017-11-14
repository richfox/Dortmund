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

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);


void ParserTest::setUp()
{}

void ParserTest::tearDown()
{}


void ParserTest::testTokenizer()
{
   vector<wstring> tokens;

   tokens = XFU::run_tokenizer(L"(11+22)*33");
   CPPUNIT_ASSERT(tokens.size() == 7);
   CPPUNIT_ASSERT(tokens[6] == L"33");
   CPPUNIT_ASSERT(XFU::run_parser(tokens)==true);

   tokens = XFU::run_tokenizer(L"11+22*33");
   CPPUNIT_ASSERT(tokens.size() == 5);
   CPPUNIT_ASSERT(tokens[4] == L"33");
   CPPUNIT_ASSERT(XFU::run_parser(tokens)==true);

   tokens = XFU::run_tokenizer(L"  (11 + 22)*33  ");
   CPPUNIT_ASSERT(tokens.size() == 7);
   CPPUNIT_ASSERT(tokens[2] == L"+");

   tokens = XFU::run_tokenizer(L"11+22*");
   CPPUNIT_ASSERT(XFU::run_parser(tokens)==false);

   tokens = XFU::run_tokenizer(L"11+(22");
   CPPUNIT_ASSERT(XFU::run_parser(tokens)==false);

   tokens = XFU::run_tokenizer(L"11+(22)");
   CPPUNIT_ASSERT(XFU::run_parser(tokens)==true);
}