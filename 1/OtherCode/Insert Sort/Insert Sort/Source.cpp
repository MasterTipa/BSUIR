#include <stdio.h>
#include <locale.h>
int main(){
	setlocale(LC_ALL, "Rus");
	int array[100], n, i, k, save;
	printf("¬ведите размерность массива\n");
	scanf_s("%d", &n);
	printf("¬ведите элементы массива\n");
	for (i = 0; i < n; i++)
		scanf_s("%d", &array[i]);
	printf("¬аш массив:");
	for (i = 0; i < n; i++)
		printf("%3d", array[i]);
	for (i = 1; i < n; i++) {
		k=i;
		while ( k > 0 && array[k - 1] > array[k] ) {
			save = array[k - 1];
			array[k - 1] = array[k];
			array[k] = save;
			k--;
		}
	}
	printf("\n¬аш отсортированный массив:");
	for (i = 0; i < n; i++)
		printf("%3d", array[i]);

return 0;
}