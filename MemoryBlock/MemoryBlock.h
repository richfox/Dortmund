#pragma once
#include <iostream>
#include <algorithm>
#include <memory>

class MemoryBlock
{
public:

	// Simple constructor that initializes the resource.
	explicit MemoryBlock(size_t length)
		: _length(length)
		, _data(std::make_shared<int>(length))
	{
		std::cout << "In MemoryBlock(size_t). length = "
			<< _length << "." << std::endl;
	}

	// Destructor.
	~MemoryBlock()
	{
		std::cout << "In ~MemoryBlock(). length = "
			<< _length << ".";

		//if (_data != NULL)
		//{
		//	std::cout << " Deleting resource.";
		//	// Delete the resource.
		//	delete[] _data;
		//}

		std::cout << std::endl;
	}

	// Copy constructor.
	MemoryBlock(const MemoryBlock& other)
		: _length(other._length)
		//, _data(new int[other._length])
	{
		std::cout << "In MemoryBlock(const MemoryBlock&). length = " 
			<< other._length << ". Copying resource." << std::endl;

		//std::copy(other._data, other._data + _length, _data);
		_data = other._data;
	}

	// Copy assignment operator.
	MemoryBlock& operator=(const MemoryBlock& other)
	{
		std::cout << "In operator=(const MemoryBlock&). length = " 
			<< other._length << ". Copying resource." << std::endl;

		if (this != &other)
		{
			// Free the existing resource.
			//delete[] _data;

			_length = other._length;
			//_data = new int[_length];
			//std::copy(other._data, other._data + _length, _data);
			_data = other._data;
		}
		return *this;
	}

	// Move constructor.
	MemoryBlock(MemoryBlock&& other)
		: _length(0)
		//,_data(NULL)
	{
		std::cout << "In MemoryBlock(MemoryBlock&&). length = " 
			<< other._length << ". Moving resource." << std::endl;

		// Copy the data pointer and its length from the 
		// source object.
		_length = other._length;
		_data = other._data;

		// Release the data pointer from the source object so that
		// the destructor does not free the memory multiple times.
		//other._data = NULL;
		//other._length = 0;
	}

	// Move assignment operator.
	MemoryBlock& operator=(MemoryBlock&& other)
	{
		std::cout << "In operator=(MemoryBlock&&). length = " 
			<< other._length << "." << std::endl;

		if (this != &other)
		{
			// Free the existing resource.
			//delete[] _data;

			// Copy the data pointer and its length from the 
			// source object.
			_length = other._length;
			_data = other._data;

			// Release the data pointer from the source object so that
			// the destructor does not free the memory multiple times.
			//other._data = NULL;
			//other._length = 0;
		}
		return *this;
	}

	// Retrieves the length of the data resource.
	size_t Length() const
	{
		return _length;
	}

private:
	size_t _length; // The length of the resource.
	//int* _data; // The resource.
	std::shared_ptr<int> _data;
};