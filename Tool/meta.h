#pragma once


#include <type_traits>
#include <vector>
#include <map>
#include <tuple>


#define NUMARGS(...) std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value

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