#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
//1.	 Создать проект консольной программы.
//2.	Создать шаблонную функцию или класс согласно заданию.
//3.	Реализовать явную специализацию шаблонной функции или класса для строк символов(char*).
//4.	В шаблонных классах использовать стандартные типы и аргументы по умолчанию.Данные в шаблонных классах хранить в статическом массиве.
//	Набор методов класса должен обеспечить основные операции с элементами объекта(добавление, удаление, поиск, просмотр, упорядочивание и т.п.) 
//	и операции над однотипными объектами(сравнение, сложение и т.п.).
//5.	Дополнительно рассмотреть реализацию наследования шаблонных классов(например, от простого базового класса).
//6.	В функции main выполнить действия с шаблонной функцией или классом, которые продемонстрируют работу методов.
//7.	Отладить и выполнить полученную программу.Проверить использование специализаций, стандартных типов и аргументов по умолчанию.
//8 Вариант.	Функция, которая удаляет элементы, удовлетворяющие условию.
template<typename S>
S input() {
	S i;
	bool fail = true;
//	std::cout << "\nInput:";
	do
	{
		std::cin >> i;
		if (std::cin.fail() || std::cin.rdbuf()->in_avail() > 1)
			std::cout << "\nError" << std::endl;
		else
			fail = false;
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	} while (fail);
	return i;
}
template<typename S>
void out(S* s, int size) {
	for (int i = 0;i < size;i++)
		std::cout << *(s+i)<<" ";
	std::cout << std::endl;
}
template<typename S>
int del(S* s,S d_element,int size) 
{
	for (int i = 0;i < size;i++)
	{
		if (*(s + i) == d_element)
		{
			for (int j = i;j < size - 1;j++)
				*(s + j) = *(s + j + 1);
			i--;size--;
		}
	}
	return size;
}
template<>
int del<char>(char* s, char d_element, int size) 
{
	for (int i = 0;i < size;i++)
	{
		if (*(s + i) == d_element)
		{
			for (int j = i;j < size - 1;j++)
				*(s + j) = *(s + j + 1);
			i--;size--;
		}
	}
	return size;
}
int main()
{
	int it_size=8, ch_size=8, dbl_size=8, it[] = { 1,2,3,4,5,5,6,7 };
	char ch[] = { 'a','b','c','o','o','y','e','w' };
	double dbl[] = { 1.7,-4.56,7.4,9.08,-4.56,2.4544,69.96,96 };
	out(it,it_size);
	out(ch,ch_size);
	out(dbl,dbl_size);
	std::cout << "Int\n";
	int dit = input<int>();
	it_size=del(it,dit,it_size);
	out(it, it_size);
	std::cout << "Char\n";
	char dch = input<char>();
	ch_size=del(ch, dch, ch_size);
	out(ch, ch_size);
	std::cout << "Double\n";
	double ddbl = input<double>();
	dbl_size=del(dbl, ddbl, dbl_size);
	out(dbl, dbl_size);
}