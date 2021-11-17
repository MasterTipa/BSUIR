#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Kotik {
	friend void print(Kotik);
public:
	friend class Veterinar;
	Kotik(string&);
	Kotik() { /*cout << "\ntry to create\n";*/ }
	~Kotik();
private:
	int id;
	string name;
	string diagnos;
};

void print(Kotik);

Kotik::Kotik(string& _name) {
	name = _name;
	id = rand() % 100;
}

Kotik::~Kotik() {
	/*cout << "\n>Destructed<\n";*/
}

class Veterinar {
public:
	void set_diagnos(Kotik& a, string _diagnos) {
		a.diagnos = _diagnos;
	}
	void set_id(Kotik& a, int _id) {
		a.id = _id;
	};
};

int main()
{
	const int size = 3;
	int _id;
	string _name;
	string _diagnos;

	srand(time_t(NULL));
	//Kotik();
	Kotik mas[size];
	Veterinar sas;

	for (int i = 0; i < size; i++)
	{
		cout << "\ninput name:";
		rewind(stdin);
		getline(cin,_name);
		mas[i] = Kotik(_name);
		print(mas[i]);

		cout << "\ninput diagnos:";
		rewind(stdin);
		getline(cin,_diagnos);
		cout << "\ninput id:";
		sas.set_diagnos(mas[i], _diagnos);
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &_id) || _id<0);
		sas.set_id(mas[i], _id);
		print(mas[i]);
	}
}

void print(Kotik _goods) {
	cout << "\nName: " << _goods.name << "\nID: " << _goods.id << "\nDiagnos: " << _goods.diagnos << endl;
}