#include <stdio.h>
#include <locale.h>
int main() {
	setlocale(LC_ALL, "Rus");
	int array[100], n, i, k, save, memory, j;
	printf("������� ����������� �������\n");
	scanf_s("%d", &n);
	printf("������� �������� �������\n");
	for (i = 0; i < n; i++)
		scanf_s("%d", &array[i]);
	printf("��� ������:");
	for (i = 0; i < n; i++)
		printf("%3d", array[i]);
	for (i = 0; i < n - 1; i++) {
		k = i;
		for (j = i+1; j < n; j++) {
			if (array[j]<array[k]) {
				k = j;
			}

		}
		save = array[i];
		array[i] = array[k];
		array[k] = save;
		

	}
	printf("��� ��������������� ������ :");
	for (i = 0; i < n; i++)
		printf("%3d", array[i]);
	return 0;
}
