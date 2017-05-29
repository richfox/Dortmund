#pragma once

#include "stdafx.h"
#include "countdownEvent.h"




// A basic agent that uses control-flow to regulate the order of program 
// execution. This agent reads numbers from a message buffer and counts the 
// number of positive and negative values.
template <typename T>
class control_flow_agent : public Concurrency::agent
{
public:
	explicit control_flow_agent(Concurrency::ISource<int>& source)
		: _source(source)
	{
	}

	// Retrieves the count of negative numbers that the agent received.
	T negatives() 
	{
		return Concurrency::receive(_negatives);
	}

	// Retrieves the count of positive numbers that the agent received.
	T positives()
	{
		return Concurrency::receive(_positives);
	}

protected:
	virtual void run() override
	{
		// Counts the number of negative and positive values that
		// the agent receives.
		size_t negative_count = 0;
		size_t positive_count = 0;

		// Read from the source buffer until we receive
		// the sentinel value of 0.
		int value = 0;      
		while ((value = Concurrency::receive(_source)) != 0)
		{
			// Send negative values to the first target and
			// non-negative values to the second target.
			if (value < 0)
				++negative_count;
			else
				++positive_count;
		}

		// Write the counts to the message buffers.
		Concurrency::send(_negatives, static_cast<T>(negative_count));
		Concurrency::send(_positives, static_cast<T>(positive_count));

		// Set the agent to the completed state.
		done();
	}
private:
	// Source message buffer to read from.
	Concurrency::ISource<int>& _source;

	// Holds the number of negative and positive numbers that the agent receives.
	Concurrency::single_assignment<T> _negatives;
	Concurrency::single_assignment<T> _positives;
};




// A basic agent that resembles control_flow_agent, but uses uses dataflow to 
// perform computations when data becomes available.
template <typename TS,typename TT>
class data_flow_agent : public Concurrency::agent
{
public:
	explicit data_flow_agent(Concurrency::ISource<TS>& source,Concurrency::ITarget<TT>& target)
		: _source(source),
		_target(target)
	{
	}

	// Retrieves the count of negative numbers that the agent received.
	size_t negatives() 
	{
		return Concurrency::receive(_negatives);
	}

	// Retrieves the count of positive numbers that the agent received.
	size_t positives()
	{
		return Concurrency::receive(_positives);
	}

protected:
	virtual void run() override
	{
		// Counts the number of negative and positive values that
		// the agent receives.
		size_t negative_count = 0;
		size_t positive_count = 0;

		// Tracks the count of active operations.
		countdown_event active;
		// An event that is set by the sentinel.
		Concurrency::event received_sentinel;

		//
		// Create the members of the dataflow network.
		//
		// Increments the active counter.
		Concurrency::transformer<int, int> increment_active([&active](int value) -> int
		{
			active.add_count();
			return value;
		});

		// Increments the count of negative values.
		Concurrency::call<int> negatives([&](int value)
		{
			++negative_count;
			// Decrement the active counter.
			active.signal();
		},[](int value)
		{
			return value < 0;
		});

		// Increments the count of positive values.
		Concurrency::call<int> positives([&](int value)
		{
			++positive_count;
			// Decrement the active counter.
			active.signal();
		},[](int value)
		{
			return value > 0;
		});

		// Receives only the sentinel value of 0.
		Concurrency::call<int> sentinel([&](int value)
		{            
			// Decrement the active counter.
			active.signal();
			// Set the sentinel event.
			received_sentinel.set();
		},[](int value)
		{ 
			return value == 0; 
		});

		// Connects the _source message buffer to the rest of the network.
		Concurrency::unbounded_buffer<int> connector;

		//
		// Connect the network.
		//
		// Connect the internal nodes of the network.
		//
		//										--> negatives
		//  								  /
		// _source --> selector --> connector ----> positives
		//									  \
		//										--> sentinel

		connector.link_target(&negatives);
		connector.link_target(&positives);
		connector.link_target(&sentinel);
		increment_active.link_target(&connector);

		// Connect the _source buffer to the internal network to 
		// begin data flow.
		_source.link_target(&increment_active);

		// Wait for the sentinel event and for all operations to finish.
		received_sentinel.wait();
		active.wait();

		// Write the counts to the message buffers.
		Concurrency::send(_negatives, negative_count);
		Concurrency::send(_positives, positive_count);


		Concurrency::send(_target,make_pair(12,wstring(L"")));
		// Set the agent to the completed state.
		done();
	}
private:
	// Source message buffer to read from.
	Concurrency::ISource<TS>& _source;
	Concurrency::ITarget<TT>& _target;

	// Holds the number of negative and positive numbers that the agent receives.
	Concurrency::single_assignment<size_t> _negatives;
	Concurrency::single_assignment<size_t> _positives;
};

