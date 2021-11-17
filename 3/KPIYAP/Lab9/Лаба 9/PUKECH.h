#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <ctime>


namespace myNamespace {
	class Exception
	{
	protected:
		int error;
	public:
		Exception()
		{
			error = 0;
		}
		Exception(int _error)
		{
			error = _error;
		}
		~Exception() { };
		void Print()
		{
			if (this->error == 1)
			{
				std::cout << "File isn't open!" << std::endl;
			}
			if (this->error == 2)
			{
				std::cout << "The vector is empty!" << std::endl;
			}
			if (this->error < 1 || this->error > 2)
			{
				int time = clock();
				std::cout << "Error time! " << time << std::endl;
			}
		}
	};
}

