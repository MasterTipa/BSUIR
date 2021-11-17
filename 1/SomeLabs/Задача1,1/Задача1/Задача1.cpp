/*1.	Ввести целое число k (1 < k < 365). Определить, каким будет k-й день года:
выходным (суббота или воскресенье) или рабочим, если 1 января — понедельник.*/

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <locale.h> //Производим подключение библиотек
int proverka() //Проверка на правильность ввода 
{
	int z;
	rewind(stdin);
	if (!scanf_s("%d", &z))
	{
		printf("\nНе корректный ввод, повторите попытку:");
		return proverka();
	}
	return z;
}

int main()

{
	setlocale(LC_ALL, "Russian");//Руссифицируем текст
	int k, m/*, n = -1*/;//Вводим переменные
	/*do
	{
		if (n != -1) printf("\nНе корректный ввод, повторите попытку:");//Проверяем на правильность ввода данных
		n = scanf_s("%d", &k);
		rewind(stdin);
	} while (!n);*/
	k = proverka();
	m = k % 7;
	if (m == 0 || m == 6) printf("Выходной\n"); else printf("Рабочий\n");//Выполняем условие
	return 0;
}
