#pragma once


#include "boost\noncopyable.hpp"

namespace XFU
{
   template<typename T>
   class Decorator : private boost::noncopyable
   {
   public:
      Decorator(T* t)
      {
         _t = t;
      }

      virtual ~Decorator()
      {}

   protected:
      T* GetDecoratedType()
      {
         return _t;
      }

      T* _t;
   };

   template<typename T>
   class NonDecoratable : private boost::noncopyable
   {
   public:
      NonDecoratable()
         :_t(nullptr)
      {}

   private:
      T* _t;
   };
}