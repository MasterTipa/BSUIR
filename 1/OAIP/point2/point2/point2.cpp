#include<stdio.h>
#include<conio.h>
#include <locale.h>
#include <windows.h>
#include<stdlib.h>

void Vvod(int *MS, int n, int k)
{
	for (int i = 0; i < n; i++)
	for (int j = 0; j < k; j++)
	{
		printf("MS[ %d ][%d] = ", i,j);
		fflush(stdin);
		//rewind(stdin);
		if (!scanf("%d", MS + i*k + j)) j--;
	}
}

void Print(int MS[], int n, int k)   // MS[] � *MS  - ������������  
{
	printf("�����  : ");
	for (int i = 0; i < n; i++)
	{
		printf("\n");
		for (int j = 0; j < k; j++)
			printf("%4d", *(MS + i*k + j));
	}
	printf("\n");
}

//--------------------------------------------- 1 -----------------------------------
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int *mt, n, m, i, j, *p=nullptr, s;
//	printf("������� ����������� ������� :");
//	printf("\n����� ����� = ");
//	if (!scanf("%d", &n)) return 0;
//	printf("\n����� �������� = ");
//	if (!scanf("%d", &m)) return 0;
//	if (!(mt= (int *)calloc(n*m, sizeof(int)))){ return 0; }
//
//	Vvod(mt,n,m);
//	system("CLS"); 
//	Print(mt,n,m);
//
//	p = mt;                 // ��������� � �� ������ �������
//	do
//	{
//		printf("\n�������� ����� ������ ��� �������� ����� �� ��������� : ");
//		rewind(stdin);
//	} while (!scanf("%d", &i) || (i >= m || i < 0));
//
//	p += i*m;               // ��������� ������������� �� ������ ������ i 
//	s = 0;                  // ����� ��������� ������ i 
//	for (i = 0; i<m; i++)   // ������� ��������� ������ 
//		s += *p++;          //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	printf("\n����� ��������� %d ������ ����� %d\n", n, s);
//	Print(mt, n, m);
//
//	free(mt);
//	return 0;
//}




////--------------------------------------------- 2 -----------------------------------
//void Vvod_float(float *MS, int n, int k)
//{
//	for (int i = 0; i < n; i++)
//	for (int j = 0; j < k; j++)
//	{
//		printf("MS[ %d ][%d] = ", i, j);
//		fflush(stdin);
//		//rewind(stdin);
//		if (!scanf("%f", MS + i*k + j)) j--;
//	}
//}
//void Print_float(float *MS, int n, int k)   // MS[] � *MS  - ������������  
//{
//	printf("�����  : ");
//	for (int i = 0; i < n; i++)
//	{
//		printf("\n");
//		for (int j = 0; j < k; j++)
//			printf("%5.2f", *(MS + i*k + j));
//	}
//	printf("\n");
//}

//// ��������� ���������� ��������� ���������� �������
//// ������������� ���� �������� ���������
//// ��������� ��������� �� �������
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int n, m, i, i1, j, j1, *p = nullptr, s;
//	float *mt;      // ��������� ��� ������������� ��������� ������ ��� ������
//	float k;
//
//	printf("������� ����������� ������� :");
//	printf("\n����� �����(��������) = ");
//	if (!scanf("%d", &n)) return 0;
//	m = n;                    // ����� ��-��� = ����� ����� 
//	if (!(mt = (float *)calloc(n*n, sizeof(float))))
//	{	puts("��� ��������� ������");
//		return 0;
//	}
//	Vvod_float(mt, n, m);
//	system("CLS");
//	printf("\n�������� �������\n ");
//	Print_float(mt, n, m);
//
//	for (i = 0; i < n - 2; i++)
//	for (j = 0; j < n - 1 - i; j++)         // ����� �������� ��� ������ � ���� MIN
//	{
//		k = *(mt + i*n + j);                // �������� MIN ��������
//		for (i1 = n - 2; i1 >= i; i1--)       // �������� ������� � ����� (� ��������� ���.)
//		for (j1 = n - 2 - i1; j1 >= 0; j1--)  // c ���������� �������� ������
//		if (mt + i*n + j < mt + i1*n + j1 &&  // ��������� ����� > �������� ������
//			k>*(mt + i1*n + j1))              // � ����� �������� < ���������
//		{
//			k = *(mt + i1*n + j1);             // ������ ��������
//			*(mt + i1*n + j1) = *(mt + i*n + j);
//			*(mt + i*n + j) = k;
//		}
//	}
//	printf("\n�������������� �������\n");
//	Print_float(mt, n, m);
//
//	free(mt);
//	return 0;
//}



//-----------------------------  3  -----------------------------------------
// ������ ������ � ���������� �������� ����� ��������� �� ���������
// ����� ���� ������� ��������� max ��-� � ���� min
int main()
{
	setlocale(LC_ALL, "Russian");
	int **p, n, s, i, j, j1, j2, sum1, sum2, sum;
	do
	{
		system("CLS");
		printf("\n������� ����������� ���������� �������\n");
		i = scanf("%d", &n);
		if (i<1)
		{
			fflush(stdin);  // ������ ������� ���������� ��� ������ �����
			continue;       // ������ ����� do {}while
		}
		s = n;             // ������� ����������
		if (!(p = (int **)malloc(sizeof(int*)*n)))
		{  printf("\n������������ ��������� ������ \n���������� ����� ����� �������");
		   continue;       // ������ �����  do {}while
		}
		for (i = 0; i<n; i++)
		if (!(*(p + i) = (int *)malloc(sizeof(int)*s)))
		{
			printf("\n������������ ��������� ������ \n���������� ����� ��-��� �������");
			for (j = 0; j<i; j++) free(*(p + j)); free(p);
			p = nullptr;   // ����� ��������� ��� �������
			break;
		}
	} while (!p);

	for (i = 0; i<n; i++)          // ���� �������
	for (j = 0; j<s; j++)
	{
		printf("������� ������� [%d][%d]= ", i, j);
		do
		{
			fflush(stdin);
		} while (!scanf("%d", *(p + i) + j));
	}
	
	system("CLS");
	printf("\n��������� ������");
	for (i = 0; i<n; i++)          // ����� �������
	{
		printf("\n");
		for (j = 0; j<s; j++)
			printf("%3d", *(*(p + i) + j));
	}

	sum = 0;                         // ����������� �����
	sum1 = *(*p + 1);                // ��� ������ max ��-�� ���� ���������
	sum2 = *(*(p + n - 1) + s - 2);  // ��� ������ min ��-�� ���� ���������
	j1 = 1; j2 = s - 2;              // ������ ������������� ��-���
	for (j = 0; j<s; j++)
	{
		for (i = 0; i<n; i++)
		if (i != j) sum += *(*(p + i) + j); // ������ ��� ����� �� ������� ���������
		else                                // ������ ������� ���������
		{
			if (sum1<sum)         // ������ ��-� � ������� ������ (��� ����������)
			{
				sum1 = sum;  j1 = j;   // ���������� ����� � ����� ��-��
				sum = 0;               // ����� ����������� ����� 
			}
		}
		if (j<s - 1 && sum2>sum)  // ������ ��-� � ������� ������ (��� ����������) 
		{
			sum2 = sum; j2 = j;       // ���������� ����� � ����� ��-��
			sum = 0;                  // ����� ����������� �����
		}
	}

	for (i = 0; i<n; i++)         // ��������� ��������� ��-���
	{
		if (i<j1) *(*(p + i) + j1) = 0;
		if (i>j2) *(*(p + i) + j2) = 0;
	}
	printf("\n\n��������������� ������");
	for (i = 0; i<n; i++)          // ����� �������
	{
		printf("\n");
		for (j = 0; j<s; j++)
			printf("%3d", *(*(p + i) + j));
	}
	for (i = 0; i<n; i++)  free(*(p + i));  free(p);
	getch();
}







