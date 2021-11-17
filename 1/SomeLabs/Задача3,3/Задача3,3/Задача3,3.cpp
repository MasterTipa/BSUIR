#include <stdio.h>
#include <conio.h>
#include <locale.h>
//13

int main()
{

	setlocale(LC_ALL, "Russian");
	int n, m, i, j, zn,s=0;
	int ms[100][100];
	scanf_s("%d%d", &n, &m);
	for (i = 0;i < n;i++)
		for (j = 0;j < m;j++)
			scanf_s("%d", &ms[i][j]);
	if (ms[0][0] < 0) zn = -1;else zn = 1;
	for (i = 0;i < n;i++)
		for (j = 0;j < m;j++)
			if (ms[i][j] < 0 && zn == 1) { s++;zn *= (-1); }
			else if (ms[i][j] > 0 && zn == -1) { s++;zn *= (-1); }

/*
for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			printf("%d ", ms[i][j]);
		printf("\n");
	}*/
	printf("%d", s);





	return 0;
}