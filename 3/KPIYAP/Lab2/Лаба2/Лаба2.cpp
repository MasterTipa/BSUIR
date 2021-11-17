#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <locale.h>
using namespace std;
//9.	Создать класс «Котик» со следующими данными: 
//id – уникальный номер, name – ФИО, diagnosis – диагноз. 
//Создать дружественный класс «Ветеринар», 
//в котором реализовать метод установки диагноза котика.
class Kotik 
{
public:
	void SetId(int x) { id = x; rewind(stdin);}
	void SetName(string s) { name = s;  rewind(stdin);}
	void SetDiagnos(string s) { diagnosis = s;};
	int GetId() { cout << "Id вашего существа";  return id; }
	string GetName() { cout << "Вы назвали существо"; return name; }
	string GetDiagnos() { cout << "Так ваше существо болеет"; return diagnosis; }
private:
	int id;
	string name;
	string diagnosis;
	friend class Veterinar;
	friend void out(Veterinar, Kotik);
public:	
	Kotik(Veterinar);
	Kotik() {};
	~Kotik() {};
};

class Veterinar
{
public:
	Veterinar(Kotik& kot) 
	{
		cout << "\nНу и какой диагноз поставил ветеринар?\n";
		string TEMP;
		rewind(stdin);
		getline(cin, TEMP);
		kot.diagnosis = TEMP;
		rewind(stdin);
		cout << "\n" << kot.GetDiagnos();
	};
	~Veterinar() {};
	void ID(Kotik& kot) 
	{
		cout << "\nНу и какой диагноз поставил ветеринар?\n";
		string TEMP;
		rewind(stdin);
		getline(cin, TEMP);
		kot.diagnosis = TEMP;
		rewind(stdin);
		/*
		void SetDiagnos(string s)
			 { kot.diagnosis = s; }
	*/}
	void IN(Kotik& kot)
	{
		cout << "Введите имя существа, которое будем лечить\n";
		rewind(stdin);
		string TEMP;
		getline(cin, TEMP);
		kot.name = TEMP;
		rewind(stdin);
	}
	void II(Kotik& kot)
	{
		cout << "\nКакое Id получит ваше существо?\n";
		rewind(stdin);
		int TEMP;
		while (!scanf_s("%d", &TEMP)) { cout << "Я знаю, что вы шутите))) "; rewind(stdin); };
		kot.id = TEMP;
		rewind(stdin);
	}
};
Kotik::Kotik(Veterinar poul) {

};
void out(Veterinar,Kotik);
void InterName(Kotik);
void InterDiagnos(Kotik);
void InterId(Kotik);
void funtime(Veterinar,Kotik);
void funtime20(Veterinar,Kotik);
int main()
{/*
	string _name;
	rewind(stdin);
	getline(cin,_name);*/
	Kotik st(Veterinar poul);
	Kotik gg;
	Veterinar gh(gg);
	Kotik mass[10];
	setlocale(LC_ALL, "Russian");//В память о великом преподователе
	//gg = new Kotik();
	//gh = new Veterinar();
	//mass = new Kotik[5];
	funtime(gh, gg);
	out(gh, gg);

	for (int i = 0;i < 10;i++)
	{
		funtime20(gh, mass[i]);
	}
 	InterName(gg);	cout << "\n" << gg.GetName();
	InterId(gg);		cout << "\n" << gg.GetId();
	InterDiagnos(gg);	cout << "\n" << gg.GetDiagnos();
	
}
void InterName(Kotik gg)
{
	cout << "Введите имя существа, которое будем лечить\n";
	string TEMP;rewind(stdin);
	getline(cin, TEMP);
	gg.SetName(TEMP);
}
void InterDiagnos(Kotik gg)
{
	cout << "\nНу и какой диагноз поставил ветеринар?\n";
	//gh->SetD(*gg);
	string TEMP;
	getline(cin, TEMP);
	gg.SetDiagnos(TEMP);
}
void InterId(Kotik gg)
{
	cout << "\nКакое Id получит ваше существо?\n";
	int TEMP;
	while (!scanf_s("%d", &TEMP)) { cout << "Я знаю, что вы шутите))) "; rewind(stdin); };
	gg.SetId(TEMP);
}
void funtime(Veterinar gh,Kotik gg)
{
	cout << "\nТеперь всё то же самое, но через дружественный класс...\n";
	gh.IN(gg);	cout << "\n" << gg.GetName();
	gh.II(gg);	cout << "\n" << gg.GetId();
	gh.ID(gg);	cout << "\n" << gg.GetDiagnos();
}
void out(Veterinar gh,Kotik gg) {
	cout << "\nТеперь всё то же самое, но через дружественную функцию...\n";
	gh.IN(gg);	cout << "\n" << gg.GetName();
	gh.II(gg);	cout << "\n" << gg.GetId();
	gh.ID(gg);	cout << "\n" << gg.GetDiagnos();
};
void funtime20(Veterinar gh, Kotik mass)
{
	//cout << "\nТеперь всё то же самое, но через дружественный класс...\n";
	gh.IN(mass);	cout << "\n" << mass.GetName();
	gh.II(mass);	cout << "\n" << mass.GetId();
	gh.ID(mass);	cout << "\n" << mass.GetDiagnos();
}