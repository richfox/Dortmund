// AsychWork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <agents.h>
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace Concurrency;

// Simulates a lengthy operation.
void perform_lengthy_operation()
{
	// Yield the current context for one second.
	wcout << L"Performing a lengthy operation, please wait";
	wait(1000);
	Sleep(1000);
}

// Computes the nth Fibonacci number.
// This function illustrates a lengthy operation and is therefore
// not optimized for performance.
int fibonacci(int n)
{
	if (n < 2)
		return n;
	return fibonacci(n-1) + fibonacci(n-2);
}


// Defines a point with x and y coordinates.
struct point
{
	int X;
	int Y;
};

// Informs the agent to end processing.
point sentinel = {0,0};

// An agent that prints point objects to the console.
class point_agent : public agent
{
public:
	explicit point_agent(unbounded_buffer<point*>& points)
		: _points(points)
	{ 
	}

	// Retrieves any exception that occured in the agent.
	bool get_error(exception& e)
	{
		return try_receive(_error, e);
	}

protected:
	// Performs the work of the agent.
	void run()
	{
		// Read from the buffer until we reach the sentinel value.
		while (true)
		{
			// Perform processing in a try block.
			try
			{
				// Read a value from the message buffer.
				point* r = receive(_points);

				// In this example, it is an error to receive a 
				// NULL point pointer. In this case, throw an exception.
				if (r == NULL)
				{
					throw exception("point must not be NULL");
				}
				// Break from the loop if we receive the 
				// sentinel value.
				else if (r == &sentinel)
				{
					break;
				}
				// Otherwise, do something with the point.
				else
				{
					// Print the point to the console.
					wcout << L"X: " << r->X << L" Y: " << r->Y << endl;
				}
			}
			// Store the error in the message buffer.
			catch (exception& e)
			{
				send(_error, e);
			}
		}
		

		// Set the agent status to done.
		done();
	}

private:
	// A message buffer that receives point objects.
	unbounded_buffer<point*>& _points;

	// A message buffer that stores error information.
	single_assignment<exception> _error;
};

int _tmain(int argc, _TCHAR* argv[])
{
	// Create a call object that prints a single character to the console.
	// A call object processes messages on a separate thread to other components that send messages to it.
	call<wchar_t> report_progress([](wchar_t c) { 
		wcout << c;
	});

	// Create a timer object that sends the dot character to the 
	// call object every 100 milliseconds.
	timer<wchar_t> progress_timer(100, L'.', &report_progress, true);

	// Start the timer on a separate context.
	progress_timer.start();

	// Perform a lengthy operation on the main context.
	perform_lengthy_operation();

	// Stop the timer and print a message.
	progress_timer.stop();

	wcout << L"done"<<endl;

	timer<wchar_t> progress_timer2(100, L'.', &report_progress, true);
	wcout << L"Computing fib(38)";
	progress_timer2.start();
	int fib38 = fibonacci(38);
	progress_timer2.stop();
	wcout<<L"result is "<<fib38<<endl;



	/////////////////////////////////////////////////////
	/***********************next test****************************/

	// Create a message buffer so that we can communicate with
	// the agent.
	unbounded_buffer<point*> buffer;

	// Create and start a point_agent object.
	point_agent a(buffer);
	a.start();

	// Send several points to the agent.
	point r1 = {10, 20};
	point r2 = {20, 30};
	point r3 = {30, 40};
	point r4 = {100,200};

	send(buffer, &r1);
	send(buffer, &r2);
	// To illustrate exception handling, send the NULL pointer to the agent.
	send(buffer, reinterpret_cast<point*>(NULL));
	send(buffer, &r3);
	send(buffer, &r4);
	send(buffer, &sentinel);
	

	// Wait for the agent to finish.
	agent::wait(&a);

	// Check whether the agent encountered an error.
	exception e;
	if (a.get_error(e))
	{
		cout << "error occured in agent: " << e.what() << endl;
	}

	// Print out agent status.
	wcout << L"the status of the agent is: ";
	switch (a.status())
	{
	case agent_created:
		wcout << L"created";
		break;
	case agent_runnable:
		wcout << L"runnable";
		break;
	case agent_started:
		wcout << L"started";
		break;
	case agent_done:
		wcout << L"done";
		break;
	case agent_canceled:
		wcout << L"canceled";
		break;
	default:
		wcout << L"unknown";
		break;
	}
	wcout << endl;



	return 0;
}

