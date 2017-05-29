// RvalueRef.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <utility>
#include <string>
#include <conio.h>
#include <memory>
#include <iostream>

using namespace std;

struct W
{
	W(int&, int&) {}
};

struct X
{
	X(const int&, int&) {}
};

struct Z
{
	Z(const int&, const int&) {}
};

template<typename T,typename A1, typename A2>
T* factory(A1&& a1, A2&& a2)
{
	return new T(a1,a2);
}

template <typename T, typename A1, typename A2>
T* factory2(A1&& a1, A2&& a2)
{
	return new T(std::forward<A1>(a1), std::forward<A2>(a2));
}

// A class that contains a memory resource.
class MemoryBlock
{
	// TODO: Add resources for the class here.
};

void g(const MemoryBlock&) 
{
	cout << "In g(const MemoryBlock&)." << endl;
}

void g(MemoryBlock&&) 
{
	cout << "In g(MemoryBlock&&)." << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int&& tmp= 3;
	const int& tmp2= tmp;

	int a=2,b=4;

	unique_ptr<W> w(factory<W>(a,b));
	unique_ptr<X> x(factory<X>(2,a));
	unique_ptr<Z> z(factory<Z>(2,2));

	unique_ptr<W> pw(factory2<W,int&,int&>(a,b));
	unique_ptr<X> px(factory2<X,const int&,int&>(2,a));
	unique_ptr<Z> pz(factory2<Z,const int&,int&&>(2,2));

	//The STL std::move function enables you to convert an object to an rvalue reference to that object.
	//Alternatively, you can use the static_cast keyword to cast an lvalue to an rvalue reference
	MemoryBlock block;
	g(block);
	g(std::move(block));
	g(static_cast<MemoryBlock&&>(block));

	return 0;
}

