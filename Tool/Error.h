#pragma once


#include "basedef.h"


namespace XFU
{
   class Error : public Object
   {
   public:
	   Error(const wchar_t* description)
		   :_description(description)
	   {}
	
	   const wchar_t* GetDescription() const
	   {
		   return _description;
	   }

   private:
	   const wchar_t* _description;
   };
}