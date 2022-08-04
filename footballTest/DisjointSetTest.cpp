#include "stdafx.h"
#include <iostream>
#include <vector>
#include "DisjointSetTest.h"
#include "..\Container\DisjointSet.h"

using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION(DisjointSetTest);


static void print_disjoint_set(const std::vector<int> &universe, DisjointSet &ds)
{
	for (int i: universe)
	{
		std::cout << ds.FindSet(i) << "(" << ds.GetRank(i) << ds.GetParent(i) << ") ";
	}
	std::cout << std::endl;
}


void DisjointSetTest::test()
{
   cout << "\r\n test disjoint-set data structure...\r\n" << endl;

	// initialize `DisjointSet` class
	DisjointSet ds;

	// create a singleton set for each element of the universe
	vector<int> universe = { 1, 2, 3, 4, 5 };
	for (int i: universe)
	{
	   ds.MakeSet(i);
	}
	print_disjoint_set(universe, ds);

	ds.Union(4, 3);		// 4 and 3 are in the same set
	print_disjoint_set(universe, ds);

	ds.Union(2, 1);		// 1 and 2 are in the same set
	print_disjoint_set(universe, ds);

	ds.Union(3, 1);		// 1, 2, 3, 4 are in the same set
	print_disjoint_set(universe, ds);
}