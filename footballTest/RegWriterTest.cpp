#include "stdafx.h"
#include "RegWriterTest.h"
#include "..\Utility\RegWriter.h"


using namespace std;
using namespace XFU;

CPPUNIT_TEST_SUITE_REGISTRATION(RegWriterTest);



void RegWriterTest::setUp()
{}

void RegWriterTest::tearDown()
{}


void RegWriterTest::test()
{
   RegWriter regw(L"Software\\xfu\\Dortmund");
   CPPUNIT_ASSERT(regw.WriteValueToReg(L"test",1));
   
   DWORD t = 0;
   CPPUNIT_ASSERT(regw.ReadValueFromReg(L"test",t));
   CPPUNIT_ASSERT(t == 1);
}