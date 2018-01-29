//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "GuardTest.h"
#include "..\Tool\Guard.h"


using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(GuardTest);

int globaltemp = 0;

const int get_temp()
{
   return globaltemp;
}

void set_temp(const int& t)
{
   globaltemp = t;
}


void GuardTest::test()
{
   class Foo
   {
   public:
      Foo():_data(0)
      {}

      const int& getdata() const
      {
         return _data;
      }

      void setdata(const int& data)
      {
         _data = data;
      }

   private:
      int _data;
   };


   Foo f;
   auto getter = [&]()->const int&{return f.getdata();};
   auto setter = [&](const int& data){f.setdata(data);};

   CPPUNIT_ASSERT(f.getdata() == 0);

   {
      XFU::Guard<int> g(getter,setter);
      f.setdata(100);
      CPPUNIT_ASSERT(f.getdata() == 100);
   }

   CPPUNIT_ASSERT(f.getdata() == 0);



   CPPUNIT_ASSERT(globaltemp == 0);

   {
      std::unique_ptr<XFU::Guard<int>> guardheap(new XFU::Guard<int>(get_temp,set_temp));
      globaltemp = 1;
      CPPUNIT_ASSERT(globaltemp == 1);
   }

   CPPUNIT_ASSERT(globaltemp == 0);
}