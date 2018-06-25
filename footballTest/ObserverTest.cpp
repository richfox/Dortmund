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
      _subject->SetX(_subject->GetX() + 1);
   }
}




void ObserverTest::setUp()
{}

void ObserverTest::tearDown()
{}


void ObserverTest::test()
{
   unique_ptr<FooSubject> sub(new FooSubject(0));
   unique_ptr<FooObserver> obs(new FooObserver(sub.get()));
   unique_ptr<FooObserver> obs2(new FooObserver(sub.get()));
   sub->NotifyEvent();

   CPPUNIT_ASSERT(sub->GetX() == 2);

   sub->Detach(obs.get());
   sub->NotifyEvent();
   CPPUNIT_ASSERT(sub->GetX() == 3);
}