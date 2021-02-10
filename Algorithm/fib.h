#pragma once

//fibonacci sequence
const static int fib[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233};

int __declspec(dllexport) fibonacci(int n);

int __declspec(dllexport) dynamic_fibonacci(int n);

int __declspec(dllexport) iterative_fibonacci(int n);