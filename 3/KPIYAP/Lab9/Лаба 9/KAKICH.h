#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <ctime>

namespace myNamespace {
	class Prods {
	private:
		int id;
		std::string name;
		std::string diagnos;
	public:
		Prods() :id(rand() % 100), name("Blank "), diagnos("Blank ") { }
		Prods(std::string t_name, std::string t_diagnos, int id = 0) :id(rand() % 100) {
			diagnos = t_diagnos;
			name = t_name;
		}
		~Prods() { }
		bool operator< (const Prods& moto) { return diagnos < moto.diagnos; }
		bool operator== (const Prods& moto) { return diagnos == moto.diagnos && name == moto.name; }
		friend std::ostream& operator<< (std::ostream& out, const Prods& Motorbike)
		{
			out << Motorbike.id << ' ' << Motorbike.name << ' ' << Motorbike.diagnos << '\n'; return out;
		}

		std::string get_name() { return name; }
		std::string get_diagnos() { return diagnos; }

	};
}
