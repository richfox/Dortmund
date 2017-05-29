//########################################################
//##                                                    ##
//##        Copyright: www.zhongwenshu.de               ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################
#pragma once

#include "boost\noncopyable.hpp"
#include "basedef.h"

#define _ ,
#define _DECL_CACHE_TYPE_(T) do{T t;}while(0)
#define _CLEAR_CACHE_TYPE_(T) do{T t;get_cache(t).ClearCache();}while(0)
#define _UPDATE_CACHE_(T,t) do{T t2;get_cache(t2).UpdateCache(t);}while(0)


template<typename T>
class ObjectCache : public Object, private boost::noncopyable
{
public:
   ObjectCache(const T& data)
      :_cached(new T(data)),
      _cleared(false)
   {}

   virtual ~ObjectCache()
   {
      if (!_cleared)
         ClearCache();
   }

   void UpdateCache(const T& data)
   {
      if (!_cleared)
         ClearCache();
      _cached = new T(data);
      _cleared = false;
   }

   void ClearCache()
   {
      delete _cached;
      _cached = nullptr;
      _cleared = true;
   }

   bool Cleared()
   {
      return _cleared;
   }

   T* Cached()
   {
      return _cached;
   }

private:
   T* _cached;
   bool _cleared;
};


//factory
template<typename T>
ObjectCache<T>& get_cache(const T& data)
{
   static ObjectCache<T> __global_cache(data);
   return __global_cache;
}