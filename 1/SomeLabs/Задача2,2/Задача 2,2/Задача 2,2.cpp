#include <stdio.h>
#include <conio.h>
#include <locale.h>
//13


int main()
{
	setlocale(LC_ALL, "Russian");										//Вводим руссификацию
	int k,n;
	double s=1;
		while (!scanf_s("%d", &n))										//Проверяем на правильность ввода данных 
		{
			printf("Не корректный ввод переменной n, повторите попытку:");
			rewind(stdin);
		};
		while (!scanf_s("%d", &k))										//Проверяем на правильность ввода данных 
		{
			printf("Не корректный ввод переменной k, повторите попытку:");
			rewind(stdin);
		};
		for (int i=2;i<=k;i++)
		{
			s += 1.0 / (i * n);
		}
		
		
		printf("\nСумма всех элементов последовательности:%f", s);
		

		
	return 0;
}