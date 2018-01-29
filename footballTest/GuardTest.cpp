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
}