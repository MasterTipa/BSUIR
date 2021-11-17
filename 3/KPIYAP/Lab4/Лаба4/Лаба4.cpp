#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
//23 - Настольные игры
//1.	По полученному базовому классу создать классы наследников по двум разным ветвям наследования(B←P1←P11 и B←P2←P21) :									+
//a)	во всех классах должны быть свои данные(характеристики объектов), расположенные в private или protected секциях;									+
//b)	во всех классах создать конструкторы инициализации объектов для всех классов(не забыть про передачу параметров в конструкции базовых классов);		+
//c)	во всех классах создать деструкторы;																												+
//d)	во всех классах создать метод вывода объекта на экран(всех его параметров);																			+
//e)	остальные методы создавать по необходимости.																										+
//2.	Создать класс с множественным наследованием(P11 ← P3 → P21).Создать в этом классе выше описанные функции											+
//(в коде функций не использовать доступ к данным через оператор разрешения зоны видимости ::).																+
//3.	В головной функции создать экземпляр класса P3.Вывести содержимое экземпляра класса P3 на экран.Проверить, что получится,							+
//если не будет использовано виртуальное наследование.																										+
//4.	Все возможные данные вводятся с клавиатуры с проверкой на корректность.Данные для объектов вводятся в main и передаются в							+
//объекты классов через конструкторы.Память выделять динамически.																							+
class BoardGame {
protected:
	string NameOfGame;
public:
	BoardGame(string name) 
	{
		this->NameOfGame=name;
	};
	~BoardGame() { cout << "\nDestroy\n"; };
	virtual void Output()
	{
		cout << NameOfGame << endl;
	};
};
class CardGame :virtual public BoardGame {
protected :
	int Cards;
public:
	CardGame (string name, int card): BoardGame(name)
	{
		this->Cards=card;
	}
	~CardGame() { cout << "\nDestroy\n"; };
	void Output()
	{
		cout << NameOfGame << "\n" << Cards;
	}
};
class FigureGame :virtual public BoardGame{
protected:
	int Figure;
public:
	FigureGame(string name, int figure) : BoardGame(name) 
	{
		this->Figure=figure;
	}
	~FigureGame() { cout << "\nDestroy\n"; };
	void Output()
	{
		cout << NameOfGame << "\n" << Figure;
	}
};
class CardType : public CardGame {
protected :
	string Type;
public:
	CardType(string name, int card, string type) :CardGame(name, card),BoardGame(name)
	{
		this->Type=type;
	};
	~CardType() { cout << "\nDestroy\n"; };
	void Output() 
	{
		cout << NameOfGame << "\n" << Cards << "\n" << Type;
	}
};
class FigureType :public FigureGame {
protected:
	string Type;
public:
	FigureType(string name, int figure, string type) :FigureGame(name, figure),BoardGame(name)
	{
		this->Type=type;
	}
	~FigureType() { cout << "\nDestroy\n"; };
	void Output() {
		cout << NameOfGame << "\n" << Figure << "\n" << Type;
	}
};
class Gamers :public FigureType, public CardType 
{
protected:
	int Number;
public:
	Gamers(string name, int figure, int card, string type1, string type2, int num) :
		FigureType(name, figure, type1), CardType(name, card, type2) , BoardGame(name)
	{
		this->Number=num;
	}
	~Gamers() { cout << "\nDestroy\n"; };
	void Output() 
	{ 
		cout << "All Figures\n" << FigureType::NameOfGame << "\n" << Figure << "\n" << FigureType::Type << "\n" << Number;
		cout<<"\nAll Card\n" << CardType::NameOfGame << "\n" << Cards << "\n" << CardType::Type << "\n" << Number;
	};

};
int input();
int main()
{
	string Name,Type1,Type2;
	cout << "Input name of game : ";
	rewind(stdin);
	getline(cin, Name);
	cout << "Input type of figure : ";
	rewind(stdin);
	getline(cin, Type1);
	cout << "Input type of card : ";
	rewind(stdin);
	getline(cin, Type2);
	cout << "Kak many figures : ";
	int Figure = input();
	cout << "Kak many cards : ";
	int Cards = input();
	cout << "Kak many members : ";
	int Number=input();
	Gamers *ss=new Gamers("Gacha",69,32,"Squrd","Poker",6);
	ss->Output();
	delete ss;
	Gamers* ll = new Gamers(Name,Figure,Cards,Type1,Type2,Number);
	ll->Output();
	delete ll;
}
int input() {
	int i;
	bool fail = true;
	cout << "\nInput:";
	do
	{
		cin >> i;
		if (cin.fail() || cin.rdbuf()->in_avail() > 1)
			cout << "\nError" << endl;
		else
			fail = false;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	} while (fail);
	return i;
}