

#include "stdafx.h"
#include "DecoratorTest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(DecoratorTest);


void DecoratorTest::setUp()
{
   _sastr.reset(new SymAttString(L"foo"));
}

void DecoratorTest::tearDown()
{
   _sastr.reset();
}


void DecoratorTest::testSymAttString()
{
   _sastr.reset(new ParentString(_sastr.release()));
   _sastr->SetWithKeyWord();
   CPPUNIT_ASSERT(_sastr->GetData() == L"%PARENT(%BASE(foo))");

   _sastr.reset(new ParentString(_sastr.release()));
   _sastr->SetWithKeyWord();
   //注意这里被装饰的最底层的类前面已经调用了SetWithKeyword，所以data为%BASE(foo)
   //再次调用SetWithKeyword即为%BASE(%BASE(foo))
   CPPUNIT_ASSERT(_sastr->GetData() == L"%PARENT(%PARENT(%BASE(%BASE(foo))))");
}


void DecoratorTest::testHighNested()
{
   _sastr.reset(new SymAttString(L"foo"));
   _sastr.reset(new ParentString(new ParentString(new ParentString(new ParentString(_sastr.release())))));
   _sastr->SetWithKeyWord();
   CPPUNIT_ASSERT(_sastr->GetData() == L"%PARENT(%PARENT(%PARENT(%PARENT(%BASE(foo)))))");
}