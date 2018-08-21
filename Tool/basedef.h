#pragma once





class Object
{
public:
   virtual ~Object()
   {}
};


class NonCopyable
{
protected:
   NonCopyable()
   {}

private:
   NonCopyable(const NonCopyable&)
   {}

   NonCopyable& operator=(const NonCopyable&)
   {
      return *this;
   }
};


class Interface : private NonCopyable
{
public:
   virtual ~Interface()
   {}
};





template<typename T>
struct RemoveRef
{
   typedef T Type;
};

template<typename T>
struct RemoveRef<T&>
{
   typedef T Type;
};

template<typename T>
struct RemoveRef<T&&>
{
   typedef T Type;
};

template<typename T>
typename RemoveRef<T>::Type&& MoveValue(T&& value)
{
   return static_cast<typename RemoveRef<T>::Type&&>(value);
}

template<typename T>
typename RemoveRef<T>::Type& LeftValue(T&& value)
{
   return static_cast<typename RemoveRef<T>::Type&>(value);
}

template<typename T>
T&& ForwardValue(typename RemoveRef<T>::Type&& value)
{
   return static_cast<T&&>(value);
}

template<typename T>
T&& ForwardValue(typename RemoveRef<T>::Type& value)
{
   return static_cast<T&&>(value);
}

struct Nothing
{};

template<typename ...TArgs>
struct FOO
{};

template<typename T>
struct KeyType
{
   typedef T Type;
};

template<typename T>
using EnumUnderlyingT = typename std::enable_if_t<std::is_enum<T>::value,typename std::underlying_type_t<T>>;

template<typename T>
constexpr inline EnumUnderlyingT<T> to_underlying(T&& t) noexcept
{
   return static_cast<typename std::underlying_type_t<T>>(t);
}

