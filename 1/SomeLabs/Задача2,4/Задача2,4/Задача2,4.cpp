#include <stdio.h>
#include <conio.h>
#include <locale.h>
//13

bool check(int n) {
	for (int i = 2;i < n / 2;i++)
	{
		if (n % i == 0) return 0;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");										//Вводим руссификацию
	int a;																//Вводим переменные
	while (!scanf_s("%d", &a))											//Проверяем на правильность ввода данных 
	{
		printf("Не корректный ввод переменной, повторите попытку:");
		rewind(stdin);
	};
	int temp = a + 1;
	while (!check(temp)) temp++;
	printf("%d", temp);
	return 0;
}