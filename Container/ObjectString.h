#pragma once


#include <utility>
#include <intrin.h>
#include <memory.h>
#include <Windows.h>
#include <vector>
#include "..\Tool\basedef.h"
#include "..\Tool\Debug.h"


#ifdef  _WIN64
#define INCRCEMENT(x)  (_InterlockedIncrement64((__int64 volatile*)(x)))
#define DECRCREMENT(x) (_InterlockedDecrement64((__int64 volatile*)(x)))
#else
#define INCRCEMENT(x)  (_InterlockedIncrement((long volatile*)(x)))
#define DECRCREMENT(x) (_InterlockedDecrement((long volatile*)(x)))
#endif





template<typename T>
class ObjectString : public Object
{
public:
    ObjectString()
    {
        _buffer = (T*)&_zero;
		_counter = 0;
        _length = 0;
    }

    ObjectString(const T& character)
    {
		_counter = new size_t(1);
        _length = 1;
        _buffer = new T[2];
        _buffer[0] = character;
        _buffer[1] = 0;
    }

	ObjectString(const T* buffer)
	{
		CHECK_ERROR(buffer!=0,L"ObjectString<T>::ObjectString(const T*):cannot construct from nullptr.");
		_counter = new size_t(1);
		_length = CalcLength(buffer);
		_buffer = new T[_length+1];
		memcpy(_buffer,buffer,(_length+1)*sizeof(T));
	}

    ObjectString(const T* buffer,size_t length)
    {
        if (length <= 0)
        {
			_buffer = (T*)&_zero;
			_counter = 0;
			_length = 0;
        }
        else
        {
			_buffer = new T[length+1];
			memcpy(_buffer,buffer,length*sizeof(T));
			_buffer[length] = 0;
			_counter = new size_t(1);
			_length = length;
        }
    }

    ObjectString(const ObjectString<T>& string)
    {
        _buffer = string._buffer;
		_counter = string._counter;
        _length = string._length;
		Increment();
    }

	ObjectString(ObjectString<T>&& string)
	{
		_buffer = string._buffer;
		_counter = string._counter;
		_length = string._length;

		string._buffer = (T*)&_zero;
		string._counter = 0;
		string._length = 0;
	}

	ObjectString(const ObjectString<T>& dst,const ObjectString<T>& src,size_t index,size_t count)
	{
		if (index==0 && count==dst._length && src._length==0)
		{
			_buffer = (T*)&_zero;
			_counter = 0;
			_length = 0;
		}
		else
		{
			_counter = new size_t(1);
			_length = dst._length-count+src._length;
			_buffer = new T[_length+1];
			memcpy(_buffer,dst._buffer,index*sizeof(T));
			memcpy(_buffer+index,src._buffer,src._length*sizeof(T));
			memcpy(_buffer+index+src._length,dst._buffer+index+count,(dst._length-index-count)*sizeof(T));
			_buffer[_length] = 0;
		}
	}

	ObjectString(const ObjectString<T>& src,size_t index,size_t length)
	{
		if (length <= 0)
		{
			_buffer = (T*)&_zero;
			_counter = 0;
			_length = 0;
		}
		else
		{
			_counter = new size_t(1);
			_length = length;
			_buffer = new T[_length+1];
			memcpy(_buffer,src._buffer+index,_length*sizeof(T));
			_buffer[_length] = 0;
		}
	}

    virtual ~ObjectString()
    {
		Decrement();
    }

    const T* Buffer() const
    {
        return _buffer;
    }

    size_t Length() const
    {
        return _length;
    }

    size_t IndexOf(T c) const
    {
        for (size_t i=0; i<_length; i++)
        {
			if (_buffer[i] == c)
				return i;
        }
		return _nopos;
    }

    size_t CountOf(const ObjectString<T>& sub) const
    {
       CHECK_ERROR(!sub.Empty(),L"ObjectString<T>::CountOf(const ObjectString<T>&):Empty substring.");
       size_t count = 0;
       size_t idx = 0;
       size_t pos = _nopos;
       do
       {
          pos = Find(sub,idx);
          if (pos != _nopos)
          {
             count++;
             idx = pos + sub.Length();
          }
          else
             break;
       }while (idx < Length());

       return count;
    }

	ObjectString<T>& Assign(const ObjectString<T>& string)
	{
		if (this != &string)
		{
			Decrement();
			_buffer = string._buffer;
			_counter = string._counter;
			_length = string._length;
			Increment();
		}
		return *this;
	}

	ObjectString<T>& Assign(ObjectString<T>&& string)
	{
		if (this != &string)
		{
			Decrement();
			_buffer = string._buffer;
			_counter = string._counter;
			_length = string._length;

			string._buffer = (T*)&_zero;
			string._counter = 0;
			string._length = 0;
		}
		return *this;
	}

	ObjectString<T>& Append(const ObjectString<T>& string)
	{
		return *this = *this + string;
	}

	size_t Compare(const ObjectString<T>& string) const
	{
		const T* bufl = _buffer;
		const T* bufr = string._buffer;
		size_t length = _length<string._length ? _length : string._length;
		while (length--)
		{
			size_t diff = *bufl++ - *bufr++;
			if (diff != 0)
			{
				return diff;
			}
		}
		return _length - string._length;
	}

	ObjectString<T>& operator=(const ObjectString<T>& string)
	{
		return Assign(string);
	}

	ObjectString<T>& operator=(ObjectString<T>&& string)
	{
		return Assign((ObjectString<T>&&)string);
	}

	ObjectString<T>& operator+=(const ObjectString<T>& string)
	{
		return Append(string);
	}

	T operator[](size_t index)
    {
		CHECK_ERROR(index>=0 && index<_length,L"ObjectString<T>::operator[](size_t):Argument index out of range.");
        return _buffer[index];
    }

    const T operator[](size_t index) const
    {
		CHECK_ERROR(index>=0 && index<_length,L"ObjectString<T>::operator[](size_t):Argument index out of range.");
        return _buffer[index];
    }

	ObjectString<T> Left(size_t count) const
	{
		CHECK_ERROR(count>=0 && count<=_length,L"ObjectString<T>::Left(size_t):Argument count out of range.");
		return ObjectString<T>(*this,0,count);
	}

	ObjectString<T> Right(size_t count) const
	{
		CHECK_ERROR(count>=0 && count<=_length,L"ObjectString<T>::Right(size_t):Argument count out of range.");
		return ObjectString<T>(*this,_length-count,count);
	}

	ObjectString<T> Substr(size_t index,size_t count=_nopos) const
	{
		CHECK_ERROR(index>=0 && index<=_length,L"ObjectString<T>::Substr(size_t,size_t):Argument index out of range.");
		CHECK_ERROR(count>=0 && index+(count==_nopos?_length-index:count)<=_length,L"ObjectString<T>::Substr(size_t,size_t):Argument count out of range.");
		return ObjectString<T>(*this,index,count==_nopos?_length-index:count);
	}

	ObjectString<T>& Insert(size_t index,const ObjectString<T>& string)
	{
		CHECK_ERROR(index>=0 && index<=_length,L"ObjectString<T>::Insert(size_t,const ObjectString<T>&):Argument index out of range.");
		return *this = ObjectString<T>(*this,string,index,0);
	}

	ObjectString<T>& Remove(size_t index,size_t count)
	{
		CHECK_ERROR(index>=0 && index<=_length,L"ObjectString<T>::Remove(size_t,size_t):Argument index out of range.");
		CHECK_ERROR(count>=0 && index+count<=_length,L"ObjectString<T>::Remove(size_t,size_t):Argument count out of range.");
		return *this = ObjectString<T>(*this,_empty,index,count);
	}

	ObjectString<T>& Replace(size_t index,size_t count,const ObjectString<T>& string)
	{
		CHECK_ERROR(index>=0 && index<=_length,L"ObjectString<T>::Replace(size_t,size_t,const ObjectString<T>&):Argument index out of range.");
		CHECK_ERROR(count>=0 && index+count<=_length,L"ObjectString<T>::Replace(size_t,size_t,const ObjectString<T>&):Argument count out of range.");
		return *this = ObjectString<T>(*this,string,index,count);
	}

    ObjectString<T>& Replace(const ObjectString<T>& target,const ObjectString<T>& placement)
    {
       size_t idx = 0;
       size_t pos = _nopos;
       do
       {
          pos = Find(target,idx);
          if (pos != _nopos)
          {
             Replace(pos,target.Length(),placement);
             idx = pos + target.Length();
          }
          else
             break;
       }while (idx < Length());

       return *this;
    }

   

   std::vector<ObjectString<T>> Split(const ObjectString<T>& separator,size_t num=0) const
   {
      CHECK_ERROR(!separator.Empty(),L"ObjectString<T>::Split(const ObjectString<T>&):Empty separator.");

      std::vector<ObjectString<T>> res;
      size_t idx = 0;
      size_t pos = _nopos;
      do
      {
         pos = Find(separator,idx);
         if (pos != _nopos)
         {
            res.push_back(Substr(idx,pos-idx));
            idx = pos + separator.Length();
         }
         else
         {
            res.push_back(Substr(idx));
            break;
         }

         if (num>0 && res.size()==num)
         {
            res.push_back(Substr(idx));
            break;
         }
      }while (idx < Length());

      return res;
   }

	ObjectString<T>& TrimLeft(T c)
	{
		size_t count = 0;
		for (size_t i=0; i<_length; i++)
        {
			if (_buffer[i] == c)
				count++;
			else
				break;
        }
		return *this = ObjectString<T>(*this,_empty,0,count);
	}

	ObjectString<T>& TrimRight(T c)
	{
		size_t count = 0;
		for (size_t i=_length-1; i>=0; i--)
		{
			if (_buffer[i] == c)
				count++;
			else
				break;
		}
		return *this = ObjectString<T>(*this,_empty,_length-count,count);
	}

	ObjectString<T>& Trim(T c)
	{
		return TrimLeft(c).TrimRight(c);
	}

    ObjectString<T>& Reverse()
    {
       size_t i = 0;
       size_t j = _length -1;
       while (i < j)
       {
          std::swap(_buffer[i],_buffer[j]);
          i++;
          j--;
       }
       return *this;
    }

	size_t Find(const T* buffer,size_t index,size_t count) const
	{
		CHECK_ERROR(index>=0 && index<=_length,L"ObjectString<T>::Find(const T*,size_t,size_t):Argument index out of range.");
		CHECK_ERROR(count>=0 && count<=CalcLength(buffer),L"ObjectString<T>::Find(size_t,size_t):Argument count out of range.");
		if (count == 0)
			return index;
		size_t nm = _length - index;
		if (index<_length && count<=nm)
		{
			const T* uptr;
			const T* vptr;
			nm -= count - 1;
			for (vptr=_buffer+index; (uptr=std::char_traits<T>::find(vptr,nm,*buffer))!=0; vptr=uptr+1)
			{
				if (std::char_traits<T>::compare(uptr,buffer,count) == 0)
					return uptr - _buffer;
				nm -= uptr - vptr + 1;
			}
		}
		return _nopos;
	}

	size_t Find(const ObjectString<T>& string,size_t index=0) const
	{
		return Find(string.Buffer(),index,string.Length());
	}

	size_t Find(const T* buffer,size_t index=0) const
	{
		return Find(buffer,index,CalcLength(buffer));
	}

	size_t Find(T c,size_t index=0) const
	{
		return Find((const T*)&c,index,1);
	}

	size_t ReverseFind(const T* buffer,size_t index,size_t count) const
	{
		CHECK_ERROR(index>=0 && index<=_length,L"ObjectString<T>::ReverseFind(const T*,size_t,size_t):Argument index out of range.");
		CHECK_ERROR(count>=0 && count<=CalcLength(buffer),L"ObjectString<T>::ReverseFind(size_t,size_t):Argument count out of range.");
		if (count == 0)
			return index;
		if (count <= _length)
		{
			const T* uptr = _buffer + (index<_length-count ? index : _length-count);
			for (; ; --uptr)
			{
				if (*uptr==*buffer && std::char_traits<T>::compare(uptr,buffer,count)==0)
					return uptr - _buffer;
				else if (uptr == _buffer)
					break;
			}
		}
		return _nopos;
	}

	size_t ReverseFind(const ObjectString<T>& string,size_t index=_nopos) const
	{
		return ReverseFind(string.Buffer(),index==_nopos?_length:index,string.Length());
	}

	size_t ReverseFind(const T* buffer,size_t index=_nopos) const
	{
		return ReverseFind(buffer,index==_nopos?_length:index,CalcLength(buffer));
	}

	size_t ReverseFind(T c,size_t index=_nopos) const
	{
		return ReverseFind((const T*)&c,index==_nopos?_length:index,1);
	}

	bool Empty() const
	{
		return _length == 0;
	}

	void Swap(ObjectString<T>& string)
	{
		if (this != &string)
		{
			ObjectString<T> tmp = *this;
			*this = string;
			string = tmp;
		}
	}

private:
	size_t CalcLength(const T* buffer) const
	{
		size_t length = 0;
		while (*buffer++)
			length++;
		return length;
	}

	void Increment() const
	{
		if (_counter)
		{
			INCRCEMENT(_counter);
		}
	}

	void Decrement() const
	{
		if (_counter)
		{
			if (DECRCREMENT(_counter) == 0)
			{
				delete[] _buffer;
				delete _counter;
			}
		}
	}

public:
	static ObjectString<T> _empty;
	static const size_t _nopos;

private:
    static const T _zero;
    mutable T* _buffer;
	mutable volatile size_t* _counter;
    mutable size_t _length;
};

template<typename T>
ObjectString<T> ObjectString<T>::_empty = ObjectString<T>();

template<typename T>
const size_t ObjectString<T>::_nopos = size_t(-1);

template<typename T>
const T ObjectString<T>::_zero = 0;


template<typename T>
inline bool operator==(const ObjectString<T>& lhs,const ObjectString<T>& rhs)
{
	return lhs.Compare(rhs) == 0;
}

template<typename T>
inline bool operator==(const ObjectString<T>& lhs,const T* rhs)
{
	return lhs.Compare(rhs) == 0;
}

template<typename T>
inline bool operator==(const T* lhs,const ObjectString<T>& rhs)
{
	return rhs.Compare(lhs) == 0;
}

template<typename T>
inline bool operator!=(const ObjectString<T>& lhs,const ObjectString<T>& rhs)
{
	return lhs.Compare(rhs) != 0;
}

template<typename T>
inline bool operator!=(const ObjectString<T>& lhs,const T* rhs)
{
	return lhs.Compare(rhs) != 0;
}

template<typename T>
inline bool operator!=(const T* lhs,const ObjectString<T>& rhs)
{
	return rhs.Compare(lhs) != 0;
}

template<typename T>
inline ObjectString<T> operator+(const ObjectString<T>& lhs,const ObjectString<T>& rhs)
{
	return ObjectString<T>(lhs,rhs,lhs.Length(),0);
}

template<typename T>
inline ObjectString<T> operator+(const ObjectString<T>& lhs,const T* rhs)
{
	return ObjectString<T>(lhs,rhs,lhs.Length(),0);
}

template<typename T>
inline ObjectString<T> operator+(const T* lhs,const ObjectString<T>& rhs)
{
	ObjectString<T> tmp(lhs);
	return ObjectString<T>(tmp,rhs,tmp.Length(),0);
}

typedef ObjectString<char> AOString;
typedef ObjectString<wchar_t> WOString;


template<typename T0,typename T1>
struct StringConverter
{};

template<>
struct StringConverter<WOString,AOString>
{
   static inline AOString Convert(const WOString& string)
   {
      int len = WideCharToMultiByte(CP_THREAD_ACP,0,string.Buffer(),-1,0,0,0,0);
      char* buffer = new char[len];
      memset(buffer,0,len*sizeof(*buffer));
      WideCharToMultiByte(CP_THREAD_ACP,0,string.Buffer(),-1,buffer,len,0,0);
      AOString s = buffer;
      delete[] buffer;
      return s;
   }
};

template<>
struct StringConverter<AOString,WOString>
{
   static inline WOString Convert(const AOString& string)
   {
      int len = MultiByteToWideChar(CP_THREAD_ACP,0,string.Buffer(),-1,0,0);
      wchar_t* buffer = new wchar_t[len];
      memset(buffer,0,len*sizeof(*buffer));
      MultiByteToWideChar(CP_THREAD_ACP,0,string.Buffer(),-1,buffer,len);
      WOString s = buffer;
      delete[] buffer;
      return s;
   }
};

template<typename T>
bool is_symmetrical(const ObjectString<T>& string)
{
   const T* begin = string.Buffer();
   const T* end = string.Buffer() + string.Length() - 1;

   while (begin < end)
   {
      if (*begin != *end)
         return false;
      begin++;
      end--;
   }

   return true;
}

template<typename T>
int edit_distance(const ObjectString<T>& lhs,const ObjectString<T>& rhs,const int dcost,const int icost,const int scost)
{
   //https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm

   int row = lhs.Length() + 1;
   int col = rhs.Length() + 1;

   std::vector<std::vector<int>> dist(row,std::vector<int>(col));
   for (int i=0; i<row; i++)
   {
      dist[i][0] = i * dcost;
   }
   for (int i=0; i<col; i++)
   {
      dist[0][i] = i * icost;
   }

   for (int i=1; i<col; i++)
   {
      for (int j=1; j<row; j++)
      {
         if (lhs[j-1] == rhs[i-1])
         {
            dist[j][i] = dist[j-1][i-1];
         }
         else
         {
            int deletion = dist[j-1][i] + dcost;
            int insertion = dist[j][i-1] + icost;
            int substitution = dist[j-1][i-1] + scost;
            dist[j][i] = min(min(deletion,insertion),substitution);
         }
      }
   }

   return dist[row-1][col-1];
}
