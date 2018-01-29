#pragma once

#include <functional>
#include "basedef.h"

namespace XFU
{
   template<typename T>
   class Guard sealed : public Object, private NonCopyable
   {
   public:
      Guard(std::function<const T()>&& getter,std::function<void(const T&)>&& setter)
         :_getter(getter),
         _setter(setter)
      {
         _data = _getter();
      }

      Guard(const T& (*getter)(),void (*setter)(const T&))
         :_getter(getter),
         _setter(setter)
      {
         _data = _getter();
      }

      ~Guard()
      {
         _setter(_data);
      }

   private:
      const std::function<const T()> _getter;
      const std::function<void(const T&)> _setter;
      T _data;
   };
}