#pragma once

#include <unordered_map>


class DisjointSet
{
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
		else
		{
			parent[x] = y;
			if (rank[x] == rank[y])
			{
			   rank[y] += 1;
			}
		}
	}

	int GetRank(int key)
	{
	   return rank[key];
	}

	int GetParent(int key)
	{
	   return parent[key];
	}

private:
	std::unordered_map<int, int> parent;

	// stores the depth of trees
	std::unordered_map<int, int> rank;
};

