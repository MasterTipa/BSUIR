#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#include"KAKICH.h"
#include "PUKECH.h"

namespace myNamespace {
	class Algorithm {
	public:
		void alg1() {
			int a, count, lnum = 0;
			std::string line,temp_word;
			std::ifstream file("1.txt");
			std::ofstream ofile("out.txt");
			if (!file || !ofile)
			{
				std::cerr << "Uh oh, SomeText.txt could not be opened for reading!" << std::endl;
				exit(1);
			}
			file.seekg(0, std::ios_base::beg);
			a = file.tellg();
			std::getline(std::cin, temp_word);
			while (file) {
				std::getline(file, line);
				bool flag = 0;
				if (!file) return;
				for (int i = 0;i < line.length();i++)
				{
					if (line[i] == temp_word[0])
					{
						for(int j = 0;j<temp_word.length();j++)
							if (line[i + j] != temp_word[j]) 
							{
								flag = 1;
								break;
							}
						if (flag == 0)
						{
							int temp = 0;
							while (i < line.length())
							{
								if (line[i] == ' ') temp++;
								i++;
							}
							ofile << temp << "\n";
						}
						if (flag == 1)
						{
							while (line[i] != ' ' && line[i] != '\n'&&i<line.length())
								i++;
							flag = 0;
							if (i == line.length()-1)
								ofile << "0 ";
						}
					}
				
				}
				
			}
			file.close();
			ofile.close();
			std::cout << "\n\n";
		}

		template<typename Prods>
		void alg2(Prods tmp, Prods start) {
			std::list<myNamespace::Prods>::iterator end=tmp.begin();
			std::list<myNamespace::Prods>::iterator find1=start.begin();
			while (end != tmp.begin())
			{
				if (end == find1) { std::cout << "I find it\n"; return; }
				end++;
			}
			std::cout << "\nI cant find\n\n";

		}

		template<typename Iterator>
		void alg3(const Iterator& head, const Iterator& tail, std::list<myNamespace::Prods>& ring) {
			Iterator start = head;
			Iterator it = tail;
			start++;
			while (start != tail) {
				if (*start == *ring.begin()) {
					Iterator tmp = start;
					start++;
					ring.erase(tmp);
					ring.push_back(myNamespace::Prods("Temp", "Temp"));
					start--;
				}
				++start;
			}
		}
	};
}


int main()
{
	myNamespace::Algorithm A;
	A.alg1();
	std::cout << "\n\n";
	myNamespace::Prods m1("Stas", "Beba");
	myNamespace::Prods m2("Max", "Norm");
	myNamespace::Prods m3("Dima", "Respect");
	myNamespace::Prods m4("Lera", "Nobrain");
	myNamespace::Prods m5("Marat", "Popabol");
	std::list<myNamespace::Prods> ring;
	std::list<myNamespace::Prods> find2;

	std::list<myNamespace::Prods>::iterator start;
	

	ring.push_back(m1);
	ring.push_back(m2);
	ring.push_back(m3);
	ring.push_back(m4);
	ring.push_back(m1);
	ring.push_back(m5);
	find2.push_back(myNamespace::Prods("Temp", "Temp"));
	start = ring.begin();
	while (start != ring.end()) {
		std::cout << *start;
		++start;
	}
	
	A.alg2(ring,find2);

	A.alg3(ring.begin(), ring.end(), ring);

	start = ring.begin();
	while (start != ring.end()) {
		std::cout << *start;
		++start;
	}

	return 0;
}