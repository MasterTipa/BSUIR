#include <stdio.h>
#include <conio.h>
#include <locale.h>
//13

int main()
{

	setlocale(LC_ALL, "Russian");
	int n, m, i, j, S = 0;
	int ms[100][100];
	scanf_s("%d%d", &n, &m);

	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if ((i + j) % 2 != 0 && n % 2 == 0) ms[i][j] = 1;
			else if ((i + j) % 2 == 0 && n % 2 == 0) ms[i][j] = 0;
			else if ((i + j) % 2 != 0 && n % 2 != 0) ms[i][j] = 0;
			else ms[i][j] = 1;
			
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			printf("%d ", ms[i][j]);
		printf("\n");
	}






	return 0;
}