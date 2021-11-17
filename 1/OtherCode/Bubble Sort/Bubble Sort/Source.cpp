#include <stdio.h>
#include <locale.h>
int main() {
	setlocale(LC_ALL, "Rus");
	int array[100], i, n, j, save;
	printf("Введите размерность вашего массива\n");
	scanf_s("%d", &n);
	printf("Введите значения элементов массива\n");
	for (i = 0; i < n; i++)
		scanf_s("%d", &array[i]);
	printf("Ваш массив:");
	for (i = 0; i < n; i++)
		printf("%4d", array[i]);		
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n -1-i; j++) {
			if (array[j] > array[j + 1]) {
				save = array[j];
				array[j] = array[j + 1];
				array[j + 1] =save;
			}
		}

	}
	printf("\n");
	printf("Отсортированный массив:");
	for (i = 0; i < n; i++)
		printf("%4d", array[i]);
	return 0;

}