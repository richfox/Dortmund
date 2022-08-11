#pragma once

#include <vector>


struct Query
{
    int L, R;
};

struct TreeNode;
class DisjointSetEx;

//Tarjan’s off-line lowest common ancestors algorithm
//O(N+Q)
//N: number of tree nodes
//Q: number of queries
void __declspec(dllexport) LCA(const TreeNode* node,DisjointSetEx& ds,const std::vector<Query>& qs);