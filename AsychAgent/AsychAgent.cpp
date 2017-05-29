// AsychAgent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "file_reader.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	// An event object that signals the end of processing.
	Concurrency::event e;

	// The components of the Adler-32 sum.
	unsigned int a = 1;
	unsigned int b = 0;

	// A call object that updates the checksum when it receives data.
	Concurrency::call<string> calculate_checksum([&] (string s)
	{
		// If the input string is empty, set the event to signal
		// the end of processing.
		if (s.size() == 0)
			e.set();
		// Perform the Adler-32 checksum algorithm.
		for_each(s.begin(), s.end(), [&] (char c)
		{
			a = (a + c) % 65521;
			b = (b + a) % 65521;
		});
	});

	// Create the agent.
	file_reader reader("readme.txt", calculate_checksum);

	// Start the agent and wait for it to complete.
	reader.start();
	Concurrency::agent::wait(&reader);

	// Wait for the call object to receive all data and complete.
	e.wait();

	// Check the file reader for errors.
	// If no error occurred, calculate the final Adler-32 sum and print it 
	// to the console.
	std::exception error;
	if (reader.get_error(error))
	{
		wcout << error.what() << endl;
	}   
	else
	{   
		unsigned int adler32_sum = (b << 16) | a;
		wcout << L"Adler-32 sum is " << hex << adler32_sum << endl;
	}

	return 0;
}

