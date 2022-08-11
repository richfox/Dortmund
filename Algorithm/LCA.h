#pragma once

#include <vector>


struct Query
{
    int L, R;
};

struct TreeNode;
class DisjointSetEx;

//Tarjan’s off-line lowest common ancestors algorithm
void __declspec(dllexport) LCA(const TreeNode* node,DisjointSetEx& ds,const std::vector<Query>& qs);