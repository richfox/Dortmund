// MemoryBlock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MemoryBlock.h"
#include <vector>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	// Create a vector object and add a few elements to it.
	vector<MemoryBlock> v;
	v.push_back(MemoryBlock(25));
	v.push_back(MemoryBlock(75));

	// Insert a new element into the second position of the vector.
	v.insert(v.begin() + 1, MemoryBlock(50));


	return 0;
}

