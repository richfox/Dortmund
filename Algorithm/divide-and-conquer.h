#pragma once


#include <vector>



//求n个整数序列的连续项的最大和，假设n为偶数

//分治算法 O(nlogn)
//递推关系：f(n) = 2f(n/2) + n + 2
//初始条件：f(1) = 1
//最大和可能在三个地方出现，或者在左半部，或者在右半部，或者跨越输入数据的中部而占据左右两部分。
//前两种情况递归求解，第三种情况的最大和可以通过求出前半部分最大和（包含前半部分最后一个元素）以及后半部分最大和（包含后半部分的第一个元素）相加而得到
//基础情况是只有一个项的序列的最大和就是这个数和0之间的较大者
int __declspec(dllexport) find_largest_sum(const std::vector<int>& seq);


//蛮力算法 O(n^2)
int __declspec(dllexport) brute_force_find_largest_sum(const std::vector<int>& seq);