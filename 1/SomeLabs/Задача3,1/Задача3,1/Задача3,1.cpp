#include <stdio.h>
#include <conio.h>
#include <locale.h>
//13

int main()
{
	
		setlocale(LC_ALL, "Russian");										
		int n, m, i, j, S = 0;
		double ms[100][100];
		scanf_s("%d%d", &n, &m);

		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++)
				scanf_s("%lf", &ms[i][j]);
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
				printf("%lf ", ms[i][j]);
			printf("\n");
		}
		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++)
				ms[i][j] *= ms[i][j];
		printf("\n");
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
				printf("%lf ", ms[i][j]);
			printf("\n");
		}





	return 0;
}