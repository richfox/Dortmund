// ParallelWork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <ppl.h>
#include <concurrent_vector.h>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>


using namespace Concurrency;
using namespace std;

// Calls the provided work function and returns the number of milliseconds 
// that it takes to call that function.
template <class Function>
__int64 time_call(Function&& f)
{
	__int64 begin = GetTickCount();
	f();
	return GetTickCount() - begin;
}

// Computes the nth Fibonacci number.
int fibonacci(int n)
{
	if(n < 2)
		return n;
	return fibonacci(n-1) + fibonacci(n-2);
}

int _tmain(int argc, _TCHAR* argv[])
{
	__int64 elapsed;

	// An array of Fibonacci numbers to compute.
	array<int, 4> a = { 24, 26, 41, 42 };

	// The results of the serial computation.
	vector<tuple<int,int>> results1;

	// The results of the parallel computation.
	concurrent_vector<tuple<int,int>> results2;

	// Use the for_each algorithm to compute the results serially.
	elapsed = time_call([&] 
	{
		for_each (a.begin(), a.end(), [&](int n) {
			results1.push_back(make_tuple(n, fibonacci(n)));
		});
	});   
	cout << "serial time: " << elapsed << " ms" << endl;

	// Use the parallel_for_each algorithm to perform the same task.
	elapsed = time_call([&] 
	{
		parallel_for_each (a.begin(), a.end(), [&](int n) {
			results2.push_back(make_tuple(n, fibonacci(n)));
		});

		// Because parallel_for_each acts concurrently, the results do not 
		// have a pre-determined order. Sort the concurrent_vector object
		// so that the results match the serial version.
		sort(results2.begin(), results2.end());
	});   
	cout << "parallel time: " << elapsed << " ms" << endl << endl;

	// Print the results.
	elapsed = time_call([&]
	{
		for_each (results2.begin(), results2.end(), [](tuple<int,int>& pair) {
			cout << "fib(" << get<0>(pair) << "): " << get<1>(pair) << endl;
		});
	});
	cout << "print time: " << elapsed << " ms" << endl << endl;

	

	return 0;
}

