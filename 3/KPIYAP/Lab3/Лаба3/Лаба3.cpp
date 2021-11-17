#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
int input();
int inputs();
class MShell 
{
public:
	MShell();
	MShell(int);
	MShell(MShell&);
	~MShell();
	friend void show(MShell);
	friend bool sravn(MShell body1, MShell body2);
	friend const MShell operator+(const MShell& left, const MShell& right)
	{
		return (left.ss + right.ss);
	};
	friend const MShell operator-(const MShell& left, const MShell& right)
	{
		return (left.ss - right.ss);
	};
	friend ostream& operator<<(ostream& out, const MShell &temp);
	void ShellSort()
	{
		int step, i, j, tmp;
		// Выбор шага
		//cout << "\n\n\n" << array.ss << " " << *array.zn << " " << *(array.zn+1) << " " << endl;
		for (step = ss / 2; step > 0; step /= 2)
			// Перечисление элементов, которые сортируются на определённом шаге
			for (i = step; i < ss; i++)
				// Перестановка элементов внутри подсписка, пока i-тый не будет отсортирован
				for (j = i - step; j >= 0 && *(zn + j) > * (zn + j + step); j -= step)
				{
					swap(*(zn + j + step), *(zn + j));
					/*tmp = *(array.zn+j);
					*(array.zn+j) = *(array.zn+j + step);
					*(array.zn+j + step) = tmp;
				*/
				}
	}
	void ReadMass(int size) {
		zn = new int[size];
		ss = size;
		for (int i = 0;i < size;i++)
			zn[i] = input();
	};
private:
	int* zn;
	int ss;
};
ostream& operator<<(ostream& out, const MShell& temp) {
	if (temp.ss == 0) out << "Size of mas ";
	else out << "Size of mas " << temp.ss <<" First element "<<*temp.zn<<endl;
	return out;
};
MShell::MShell()
{
	//cout << "1"<<endl;
	zn = new int[1];
	ss = 1;
		zn[ss-1] = rand() % 100;
};
MShell::MShell(int size)
{
	//cout << "2" << endl;
	zn = new int[size];
	ss = size;
	for (int i = 0;i < size;i++)
		zn[i] = rand() % 100;
};
MShell::MShell(MShell& copy)
{
	cout << "3asd" << endl;
	ss = copy.ss;
	zn = new int[ss];
	for (int i = 0;i < ss;i++)
		zn[i] = copy.zn[i];
};
MShell::~MShell() {
	//cout << "4gg" << endl;
	while(!zn) delete[] zn;
};
void show(MShell);
bool sravn(MShell body1, MShell body2);
int main()
{
	int sz = 5;
	srand(time(NULL));
	MShell mas;
	mas=MShell();		//Конструктор по умолчанию
	show(mas);			//Вывод созданной ерунды
	mas=MShell(sz);		//Конструктор с параметром
	show(mas);			//Вывод созданной ерунды
	mas.ShellSort();	//Его сортировка
	show(mas);			//Вывод отсортированной ерунды
	cout << "Size of mas : ";
	sz=inputs();		//Ввод размера массива
	cout << "\nTime to read mas : ";
	mas.ReadMass(sz);	//Вводим значения новоиспечённого массива
	show(mas);			//Выводим данный массив
	mas.ShellSort();	//Сортировка нового массива
	show(mas);			//Показать красату
	MShell mas2;		//Создаём ещё один экземпляр класса
	mas2 = MShell(5);
	cout << "Work with operator +, - and << \n";
	MShell mas3;
	mas3=mas + mas2;	//operator +
	show(mas3);			//показываю новый увеличенный массив с рандомными значениями
	cout << mas3;		//operator <<
	if (sravn(mas2 , mas))
	mas3 = mas2 - mas;	//operator -
	else mas3 = mas - mas2;
	show(mas3);			//Всё то же самое
	cout << mas3;
	cout << "\nMake mas of classes\n Haw many?";
	int gg=input();
	MShell* ms;			//Массив классов
	ms=new MShell[gg];	//Выделяю память под массив
	for (int i = 0;i < gg;i++)
	{
		int sz = input();
		ms[i].ReadMass(sz);
		show(ms[i]);
	}
	return 0;
}
void show(MShell body) 
{
	for (int i = 0;i < body.ss;i++)
		cout << body.zn[i]<<" ";
	cout << endl;
}
bool sravn(MShell body1, MShell body2) {
	if (body1.ss > body2.ss) return 1; else return 0;
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
int inputs() {

	int i;
	bool fail = true;
	cout << "\nInput:";
	do
	{
		cin >> i;
		if (cin.fail() || cin.rdbuf()->in_avail() > 1 || i<=0)
			cout << "\nError" << endl;
		else
			fail = false;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	} while (fail);
	return i;
}