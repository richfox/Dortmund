// Dataflow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FlowAgent.h"



using namespace std;





namespace
{
	// Sends a number of random values to the provided message buffer.
	void send_values(Concurrency::ITarget<int>& source, int sentinel, size_t count)
	{
		// Send a series of random numbers to the source buffer.
		mt19937 rnd(42);
		for (size_t i = 0; i < count; ++i)
		{
			// Generate a random number that is not equal to the sentinel value.
			int n;
			while ((n = rnd()) == sentinel);

			Concurrency::asend(source, n);      
		}
		// Send the sentinel value.
		Concurrency::asend(source, sentinel);   
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	// Signals to the agent that there are no more values to process.
	const int sentinel = 0;
	// The number of samples to send to each agent.
	const size_t count = 200000;

	//
	// Use a control-flow to process a series of random numbers.
	//
	wcout << L"Control-flow without agent" << endl;

	mt19937 rnd(42);
	int plus=0,minus=0;
	for (size_t i = 0; i < count; ++i)
	{
		// Generate a random number that is not equal to the sentinel value.
		int n = rnd();

		if (n <0)
			minus++;
		else if (n>0)
			plus++;
		else
			;
	}

	// Print the count of negative and positive numbers.
	wcout << L"There are " << minus
		<< L" negative numbers."<< endl;
	wcout << L"There are " << plus
		<< L" positive numbers."<< endl;  


	// The source buffer that the application writes numbers to and 
	// the agents read numbers from.
	Concurrency::unbounded_buffer<int> source;

	//
	// Use a control-flow agent to process a series of random numbers.
	//
	wcout << L"Control-flow agent:" << endl;

	// Create and start the agent.
	//新的线程随着异步代理的创建被创建！！
	control_flow_agent<size_t> cf_agent(source);
	cf_agent.start();

	// Send values to the agent.
	//新的线程随着异步消息块的接收消息被创建！！
	send_values(source, sentinel, count);

	// Wait for the agent to finish.
	Concurrency::agent::wait(&cf_agent);

	// Print the count of negative and positive numbers.
	wcout << L"There are " << cf_agent.negatives() 
		<< L" negative numbers."<< endl;
	wcout << L"There are " << cf_agent.positives() 
		<< L" positive numbers."<< endl;  



	//
	// Perform the same task, but this time with a dataflow agent.
	//
	wcout << L"Dataflow agent:" << endl;

	Concurrency::event e;
	typedef pair<int,wstring> tt;
	tt a;
	Concurrency::call<tt> target([&](tt i)
	{
		a = i;
	});

	// Create and start the agent. 
	//新的线程随着异步代理的创建被创建！！
	data_flow_agent<int,tt> df_agent(source,target);
	df_agent.start();

	// Send values to the agent.
	//新的线程随着异步消息块的接收消息被创建！！
	send_values(source, sentinel, count);
	e.set();

	// Wait for the agent to finish.
	Concurrency::agent::wait(&df_agent);
	e.wait();

	// Print the count of negative and positive numbers.
	wcout << L"There are " << df_agent.negatives() 
		<< L" negative numbers."<< endl;
	wcout << L"There are " << df_agent.positives() 
		<< L" positive numbers."<< endl;

	return 0;
}

