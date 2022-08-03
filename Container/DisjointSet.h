#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>


class DisjointSet
{
private:
	std::unordered_map<int, int> parent;

	// stores the depth of trees
	std::unordered_map<int, int> rank;

public:
	// perform MakeSet operation
	void MakeSet(const int i)
	{
		parent[i] = i;
		rank[i] = 0;
	}

	// find the root of the set in which element `k` belongs
	int FindSet(int k)
	{
		// if `k` is not the root
		if (parent[k] != k)
		{
			// path compression
			parent[k] = FindSet(parent[k]);
		}

		return parent[k];
	}

	// Perform Union of two subsets
	void Union(int a, int b)
	{
		// find the root of the sets in which elements `x` and `y` belongs
		int x = FindSet(a);
		int y = FindSet(b);

		// if `x` and `y` are present in the same set
		if (x == y)
		{
			return;
		}

		// Always attach a smaller depth tree under the root of the deeper tree.
		if (rank[x] > rank[y])
		{
			parent[y] = x;
		}
		else if (rank[x] < rank[y])
		{
			parent[x] = y;
		}
		else
		{
			parent[x] = y;
			rank[y]++;
		}
	}
};

void printSets(const std::vector<int> &universe, DisjointSet &ds)
{
	for (int i: universe)
	{
		std::cout << ds.FindSet(i) << ' ';
	}
	std::cout << std::endl;
}