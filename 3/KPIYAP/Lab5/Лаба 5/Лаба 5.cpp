#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
//23 - Настольные игры
//1.	Базовый класс должен быть абстрактным.																													+
//2.	По полученному базовому классу создать классы наследников по двум разным ветвям наследования(B←P1←P11 и B←P2) :											+
//	a.во всех классах должны быть свои данные(характеристики объектов), расположенные в private или protected секциях;											+
//	b.во всех классах создать конструкторы инициализации объектов для всех классов(не забыть про передачу параметров в конструкции базовых классов);			+
//	c.во всех классах создать деструкторы;																														+
//	d.остальные методы создавать по необходимости.																												+
//3.	Создать в базовом классе чисто виртуальные функции расчета(например, расчет площади фигуры и т.п.) и вывода объекта на экран(всех его параметров).		+
//	Выполнить реализацию этих виртуальных функций в классах наследниках.																						+
//4.	Задать в базовом классе деструктор как виртуальный.																										+
//5.	В головной функции динамически создать массив указателей на базовый класс.Заполнить массив указателями на динамически создаваемые объекты				+
//	производных классов(P1, P11, P2).Для каждого элемента массива проверить работу виртуальных функций.Удалить из памяти динамически выделенные объекты.		+
//6.	Всё взаимодействие с экземплярами производных классов производить через указатель на базовый класс.														+
//7.	Сгенерировать диаграмму классов																															+

class BoardGame {
protected:
	string NameOfGame;
public:
	BoardGame(string name)
	{
		this->NameOfGame = name;
	};
	virtual ~BoardGame() { cout << "\nDestroy\n"; };
	virtual void Output()
	{
		cout << NameOfGame << endl;
	};
	//virtual int HManyF() = 0;
	//virtual int HManyC() = 0;
	virtual int FCGame() = 0;
};
class CardGame :virtual public BoardGame {
protected:
	int Cards;
public:
	CardGame(string name, int card) : BoardGame(name)
	{
		this->Cards = card;
	}
	~CardGame() { cout << "\nDestroy\n"; };
	void Output()
	{
		cout << NameOfGame << "\n" << Cards;
	}
	int FCGame() override 
	{
		cout << "\n32 - " << Cards << " = ";
		int gg = 32 - Cards;
		return gg;
	};
};
class FigureGame :virtual public BoardGame {
protected:
	int Figure;
public:
	FigureGame(string name, int figure) : BoardGame(name)
	{
		this->Figure = figure;
	}
	~FigureGame() { cout << "\nDestroy\n"; };
	void Output()
	{
		cout << NameOfGame << "\n" << Figure;
	}
	int FCGame() override
	{
		cout << "\n16 - " << Figure << " = ";
		int gg = 16 - Figure;
		return gg;
	}
};
class CardType : public CardGame {
protected:
	string Type;
public:
	CardType(string name, int card, string type) :CardGame(name, card), BoardGame(name)
	{
		this->Type = type;
	};
	~CardType() { cout << "\nDestroy\n"; };
	void Output()
	{
		cout << NameOfGame << "\n" << Cards << "\n" << Type;
	}
};
//class FigureType :public FigureGame {
//protected:
//	string Type;
//public:
//	FigureType(string name, int figure, string type) :FigureGame(name, figure), BoardGame(name)
//	{
//		this->Type = type;
//	}
//	~FigureType() { cout << "\nDestroy\n"; };
//	void Output() {
//		cout << NameOfGame << "\n" << Figure << "\n" << Type;
//	}
//};
//class Gamers :public FigureType, public CardType
//{
//protected:
//	int Number;
//public:
//	Gamers(string name, int figure, int card, string type1, string type2, int num) :
//		FigureType(name, figure, type1), CardType(name, card, type2), BoardGame(name)
//	{
//		this->Number = num;
//	}
//	~Gamers() { cout << "\nDestroy\n"; };
//	void Output()
//	{
//		cout << "All Figures\n" << FigureType::NameOfGame << "\n" << Figure << "\n" << FigureType::Type << "\n" << Number;
//		cout << "\nAll Card\n" << CardType::NameOfGame << "\n" << Cards << "\n" << CardType::Type << "\n" << Number;
//	};
//	int FCGame() override
//	{
//		cout << "\nFigure > Cards = ";
//		return Figure > Cards;
//	}
//};
int input();
int main()
{
	string Name, Type1, Type2;
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
	int Number = input();
	
	BoardGame* mas[2];
	mas[0] = new CardGame(Name,Cards);
	mas[1] = new FigureGame(Name,Figure);
	//mas[2] = new CardType(Name,Figure,Cards,Type1,Type2,Number);
	for (int i = 0;i < 2;i++)
	{
		mas[i]->Output();
		cout << mas[i]->FCGame() << endl;
	}
	for (int i = 0; i < 3; i++) {
		delete mas[i];
	}

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