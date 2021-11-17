#include <stdio.h>
#include <conio.h>
#include <locale.h>
//13


int main()
{
	setlocale(LC_ALL, "Russian");										//Вводим руссификацию
	int a, b, p, a1, b1;													//Вводим переменные
	while (!scanf_s("%d", &a))										//Проверяем на правильность ввода данных 
	{
		printf("Не корректный ввод 1-й переменной, повторите попытку:");
		rewind(stdin);
	};
	while (!scanf_s("%d", &b))										//Проверяем на правильность ввода данных 
	{
		printf("Не корректный ввод 2-й переменной, повторите попытку:");
		rewind(stdin);
	};
	if (a > b) p = b; else p = a;
	do
	{
		a1 = a % p;
		b1 = b % p;
		p--;
	} 
	while (a1!=0 || b1!=0);
	p++;
	printf("Наибольший общий делитель :%d", p);
	
	return 0;
}