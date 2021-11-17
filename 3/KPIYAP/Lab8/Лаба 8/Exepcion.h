#pragma once
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
class Exception
{
protected:
	int error;
public:
	Exception() :error(0) {}
	Exception(int error)
	{
		this->error = error;
	}
	~Exception() { };


	void Print()
	{
		switch (error)
		{
		case 1: cout << "File isn't open!" << endl;
			break;
		case 2: cout << "The class is empty!" << endl;
			break;
		case 3: cout << "The stack is empty!" << endl;
			break;
		}
	}
};