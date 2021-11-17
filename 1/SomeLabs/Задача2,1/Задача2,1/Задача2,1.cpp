#include <stdio.h>
#include <conio.h>
#include <locale.h>
//13


int main()
{	setlocale(LC_ALL, "Russian");								//Вводим руссификацию
int a,b=0;														//Вводим переменные
	do
{
		while (!scanf_s("%d", &a))								//Проверяем на правильность ввода данных 
		{
			printf("Не корректный ввод, повторите попытку:");
			rewind(stdin);
		};
	if (a > 0) b += a;											//Производим счёт данных
} while (a != 0);
printf("Сумма элементов больше 0 = %d", b);

	return 0;
}