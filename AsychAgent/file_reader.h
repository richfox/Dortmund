#pragma once


#include "stdafx.h"





class file_reader : public Concurrency::agent
{
public:
	explicit file_reader(const std::string& file_name, 
		Concurrency::ITarget<std::string>& target)
		: _file_name(file_name)
		, _target(target)
	{
	}

	explicit file_reader(const std::string& file_name, 
		Concurrency::ITarget<std::string>& target,
		Concurrency::Scheduler& scheduler)
		: agent(scheduler)
		, _file_name(file_name)
		, _target(target)
	{
	}

	explicit file_reader(const std::string& file_name, 
		Concurrency::ITarget<std::string>& target,
		Concurrency::ScheduleGroup& group)
		: agent(group) 
		, _file_name(file_name)
		, _target(target)
	{
	}

	// Retrieves any error that occurs during the life of the agent.
	bool get_error(std::exception& e)
	{
		return try_receive(_error, e);
	}

protected:
	void run()
	{
		FILE* stream;
		try
		{
			// Open the file.
			if (fopen_s(&stream, _file_name.c_str(), "r") != 0)
			{
				// Throw an exception if an error occurs.            
				throw std::exception("Failed to open input file.");
			}

			// Create a buffer to hold file data.
			char buf[1024];

			// Set the buffer size.
			setvbuf(stream, buf, _IOFBF, sizeof buf);

			std::ostream_iterator<std::string> ofile(std::cout,"");
			std::list<std::string> text;

			// Read the contents of the file and send the contents
			// to the target.
			while (fgets(buf, sizeof buf, stream))
			{
				text.push_back(buf);
				asend(_target, std::string(buf));
			}

			std::copy(text.begin(),text.end(),ofile);
			std::cout << "\n\n";

			// Send the empty string to the target to indicate the end of processing.
			asend(_target, std::string(""));

			// Close the file.
			fclose(stream);
		}
		catch (const std::exception& e)
		{
			// Send the empty string to the target to indicate the end of processing.
			asend(_target, std::string(""));

			// Write the exception to the error buffer.
			send(_error, e);
		}

		// Set the status of the agent to agent_done.
		done();
	}

private:
	std::string _file_name;
	Concurrency::ITarget<std::string>& _target;
	Concurrency::overwrite_buffer<std::exception> _error;
};