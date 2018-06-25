#pragma once


#include "cppunit\TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"
#include "..\DesignPattern\Observer.h"


namespace XFU
{
   class FooSubject : public Subject
   {
   public:
      FooSubject(int x)
         :Subject(),
         _x(x)
      {}

      virtual ~FooSubject()
      {}

      void NotifyEvent();

      int GetX()
      {
         return _x;
      }

      void SetX(int x)
      {
         _x = x;
      }

   private:
      int _x;
   };

   class FooObserver : public Observer
   {
   public:
      FooObserver(FooSubject* subject)
         :Observer(),
         _subject(subject)
      {
         _subject->Attach(this);
      }

      virtual ~FooObserver()
      {
         _subject->Detach(this);
      }

      virtual void Update(const ObserverEvent& event) override;

   protected:
      FooSubject* _subject;
   };
}


class ObserverTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(ObserverTest);
   CPPUNIT_TEST(test);
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void test();
};