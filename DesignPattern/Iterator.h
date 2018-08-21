//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################
#pragma once

#include "basedef.h"





namespace XFU
{
   template<typename T>
   class Iterator : public virtual Interface
   {
   public:
      typedef T ElemType;

      virtual Iterator<T>* Clone() const = 0;
      virtual const T& Current() const = 0;
      virtual int Index() const = 0;
      virtual bool Next() = 0;
      virtual void Reset() = 0;
   };
}


