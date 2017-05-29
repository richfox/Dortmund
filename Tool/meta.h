#pragma once


#include <type_traits>
#include <vector>
#include <map>


namespace XFU
{
   //TODO
   //http://en.cppreference.com/w/cpp/types/void_t

   template<typename T,typename=void>
   struct Iterable : std::false_type
   {};

   //template<typename T>
   //struct Iterable<T,std::>
}