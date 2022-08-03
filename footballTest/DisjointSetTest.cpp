#include "stdafx.h"
#include "DisjointSetTest.h"
#include "..\Container\DisjointSet.h"

using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION(DisjointSetTest);


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
	printSets(universe, ds);

	ds.Union(4, 3);		// 4 and 3 are in the same set
	printSets(universe, ds);

	ds.Union(2, 1);		// 1 and 2 are in the same set
	printSets(universe, ds);

	ds.Union(1, 3);		// 1, 2, 3, 4 are in the same set
	printSets(universe, ds);
}