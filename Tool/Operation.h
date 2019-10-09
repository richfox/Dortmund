#pragma once




#define FOR_INDEX(TYPE,VAR,VALUE)\
   if(bool __scope_flag__=true)\
      for(TYPE VAR = VALUE;__scope_flag__;__scope_flag__=false)

#define FOR_EACH(VAR,IT,INDEX)\
   FOR_INDEX(int,INDEX,0)\
   for (auto IT=VAR.begin(); IT!=VAR.end(); IT++,INDEX++)


template<typename T>
using EnumUnderlyingT = typename std::enable_if_t<std::is_enum<T>::value,typename std::underlying_type_t<T>>;

template<typename T>
constexpr inline EnumUnderlyingT<T> to_underlying(T&& t) noexcept
{
   return static_cast<typename std::underlying_type_t<T>>(t);
}