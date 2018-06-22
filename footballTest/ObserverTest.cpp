#include "stdafx.h"
#include "ObserverTest.h"



using namespace std;
using namespace XFU;

CPPUNIT_TEST_SUITE_REGISTRATION(ObserverTest);



void FooSubject::NotifyEvent()
{
   Notify(ObserverEvent(L"TEST"));
}


void FooObserver::Update(const ObserverEvent& event)
{
   if (event.Getid() == L"TEST")
   {
      //do someting
   }
}




void ObserverTest::setUp()
{}

void ObserverTest::tearDown()
{}


void ObserverTest::test()
{}