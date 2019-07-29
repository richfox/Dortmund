#pragma once

#include "basedef.h"

namespace XFU
{
   template<typename R,typename... A>
   class Invoker : public Object
   {
   public:
      virtual R Invoke(A&&... args) = 0;
      virtual R operator()(A&&... args)
      {
         return Invoke(std::forward<A>(args)...);
      }
   };


   template<typename R,typename... A>
   class FreeInvoker sealed : public Invoker<R,A...>
   {
   public:
      FreeInvoker(R(*freefunc)(A...))
         :_freefunc(freefunc)
      {}

      virtual R Invoke(A&&... args) override
      {
         return _freefunc(std::forward<A>(args)...);
      }

   private:
      R(*_freefunc)(A... args);
   };


   template<typename C,typename R,typename... A>
   class MemberInvoker sealed : public Invoker<R,A...>
   {
   public:
      MemberInvoker(C* sender,R(C::*memberfunc)(A...))
         :_sender(sender),
         _memberfunc(memberfunc)
      {}

      virtual R Invoke(A&&... args) override
      {
         return (_sender->*_memberfunc)(std::forward<A>(args)...);
      }

   private:
      C* _sender;
      R(C::*_memberfunc)(A... args);
   };
}