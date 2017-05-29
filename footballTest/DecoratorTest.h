#pragma once

#include <string>
#include <memory>
#include "..\DesignPattern\Decorator.h"
#include "cppunit\TestFixture.h"
#include "cppunit\extensions\HelperMacros.h"


/***********************************************************/
/* Klasse f�r %BASE                                        */
/***********************************************************/
class SymAttString
{
public:
   SymAttString(const std::wstring& data)
      :_data(data)
   {}

   virtual ~SymAttString()
   {}

   virtual void SetWithKeyWord()
   {
      _data = L"%BASE(" + _data + L")";
   }

   const std::wstring GetData() const
   {
      return _data;
   }

protected:
   std::wstring _data;
};

/***********************************************************/
/* Klasse f�r Decorator von %BASE                          */
/***********************************************************/
class SymAttStringDecorator : public XFU::Decorator<SymAttString>
{
protected:
   SymAttStringDecorator(SymAttString* str)
      :XFU::Decorator<SymAttString>(str)
   {
      _sastr = GetDecoratedType();
   }

   virtual ~SymAttStringDecorator()
   {}

   void SetWithKeyWord()
   {
      _sastr->SetWithKeyWord();
   }

   const std::wstring GetData() const
   {
      return _sastr->GetData();
   }

   SymAttString* _sastr;
};

/***********************************************************/
/* Klasse f�r %PARENT(%BASE)                               */
/***********************************************************/
class ParentString : public SymAttString, public SymAttStringDecorator
{
public:
   ParentString(SymAttString* sa)
      :SymAttString(*sa),
      SymAttStringDecorator(sa)
   {}

   virtual ~ParentString()
   {}

   virtual void SetWithKeyWord()
   {
      _data = L"%PARENT(";

      SymAttStringDecorator::SetWithKeyWord();
      _data.append(SymAttStringDecorator::GetData());

      _data.append(L")");
   }
};

/***********************************************************/
/* Klasse f�r %NOBASE                          */
/***********************************************************/
class NoSymAttString : public XFU::NonDecoratable<NoSymAttString>
{
public:
   NoSymAttString(const std::wstring& data)
      :_data(data)
   {}

   virtual ~NoSymAttString()
   {}

   virtual void SetWithKeyWord()
   {
      _data = L"%NOBASE(" + _data + L")";
   }

   const std::wstring GetData() const
   {
      return _data;
   }

protected:
   std::wstring _data;
};


/***********************************************************/
/* Klasse f�r Test                      */
/***********************************************************/
class DecoratorTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(DecoratorTest);
   CPPUNIT_TEST(testSymAttString);
   CPPUNIT_TEST(testHighNested);
   CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSymAttString();
    void testHighNested();

private:
   std::unique_ptr<SymAttString> _sastr;
};