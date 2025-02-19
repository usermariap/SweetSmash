#pragma once
#include "Sweet.h"

class table
{
	Sweet ** data;

public:

	table()
	{
		data = new Sweet*[64];
	}

	~table()
	{
		if (data)
		{
			delete[] data;
			data = nullptr;
			
		}
	}

	Sweet* operator () (unsigned int row, unsigned int col,Sweet* datas) const
	{
		if (row >= 8 || col >= 8)
			throw 0;
		data[8 * row + col] = datas;
		return data[8 * row + col];
	}

	Sweet* operator () (unsigned int row, unsigned int col) const
	{
		if (row >= 8 || col >= 8) return nullptr;
		
		return data[8 * row + col];
	}
};