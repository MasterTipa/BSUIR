#include<stdio.h>
#include<conio.h>
#include <locale.h>
#include <windows.h>
#include<stdlib.h>

//void Vvod(int n, int *MS,int k)
//{
//       !!!!!!!!!!!!!!!!!!!     ��������  
//	printf("������� �������� � ����� MS ");
//	if (n == 1) printf("�� �����������\n");
//	else  printf("�� ��������\n");
//	int i = 0;
//	int j;
//	while (i < k)
//	{
//		printf("MS[ %d ] = ", i);
//		j=scanf("%d", MS+i);
//		if (j && (i == 0 || 
//			      (n == 1 && *(MS+i) >= *(MS+i-1)) ||
//				  (n == 2 && *(MS+i) <= *(MS+i-1)) ) ) i++;
//	}
//}

void Vvod(int *MS,int k)
{
	int i = 0;
	int j;
	//       !!!!!!!!!!!!!!!!!!!     ��������   
	while (i < k)
	{
		printf("MS[ %d ] = ", i);
		fflush(stdin);
		//rewind(stdin);
		if (scanf("%d", MS+i)) i++;
	}
}

void Print(int MS[], int k)      //  ����� MS[] � *MS  - ������������  
{
	printf("�����  : ");
	for (int i = 0; i < k; i++)
		printf("%4d", MS[i]);
	printf("\n");
}

//--------------------------------------------- 1 -----------------------------------
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int *ms1, *ms2, *ms3, n1, n2, i1, i2, i3, k1, k2;
//	printf("������� ����������� ������� ������� n1= ");
//	scanf("%d", &n1);
//	printf("������� ����������� ������� ������� n2= ");
//	scanf("%d", &n2);
//	if (!n1 && !n2) return 0;
//	if (!(ms1 = (int *)calloc(n1, sizeof(int)))){ return 0; }
//	if (!(ms2 = (int *)calloc(n2, sizeof(int))))
//	{
//		free(ms1); return 0;
//	}
//	if (!(ms3 = (int *)calloc(n1 + n2, sizeof(int))))
//	{
//		free(ms1); free(ms2); return 0;
//	}	
//	Vvod(1,ms1,n1);
//	system("CLS"); 
//	Vvod(2, ms2, n2);
//	system("CLS");
//	Print(ms1,n1);
//	Print(ms2,n2);
//
//	i1 = i3 = 0;  // ms1 � ms3 - � ������ 
//	i2 = n2 - 1;  // ms2 � �����
//	do
//	{         // ���� ���������� ��-��� �� �������  ms1 �  ms3
//		while (*(ms1 + i1) <= *(ms2 + i2) && i1<n1) *(ms3 + i3++) = *(ms1 + i1++);
//		if (i1 >= n1) break; 
//	      	  // ���� ���������� ��-��� �� �������  ms2 �  ms3
//		while (*(ms1 + i1)> *(ms2 + i2) && i2<n2) *(ms3 + i3++) = *(ms2 + i2--);
//	} while (i1<n1 && i2>=0);
//
//	while (i1<n1) *(ms3 + i3++) = *(ms1 + i1++);   // ���� �������� ��-��� �� �������  ms1 �  ms3
//	while (i2 >= 0) *(ms3 + i3++) = *(ms2 + i2--); // ���� �������� ��-��� �� �������  ms2 �  ms3
//
//	Print(ms3, n1+n2);
//	free(ms1); free(ms2); free(ms3)
//	return 0;
//}




//--------------------------------------------- 2 -----------------------------------
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int *ms, n1, i, j, k;
//	printf("������� ����������� ������� n1= ");
//	scanf("%d", &n1);
//	if (!n1) return 0;
//	if (!(ms = (int *)calloc(n1, sizeof(int)))) { return 0; }
//
//	Vvod(ms, n1);
//	system("CLS");
//	Print(ms, n1);
//
//	while (1)
//	{
//		printf("������� ����� ����������� � ������ k= ");
//		scanf("%d", &k);
//		if (!k) break;               
//		i = 0;
//        while (i<n1 && *(ms + i) < k) i++; // ���� ������ ����� ��� ���������� �����
//		ms = (int *)realloc(ms, sizeof(int)*(n1+1));  // ���������� ������ ��� ������� �� ���� �������
//		if (!ms) break;
//		if (i==n1)   // � ������� ��� ������� ���������� - ���������� � �����
//		   *(ms + i) = k;    // ���������� ���������� ��-�� � ����� ������� 
//		else
//		{
//			j = n1;          // j �� ����� ������� (������)
//			while (j > i)    // ���� ������ ��-��� ������� � ����� �� ���� ������� 
//				*(ms + j--) = *(ms + j - 1);
//			*(ms + i) = k;   // �������� � �������������� �����
//		}
//		n1++;                // ��������� ������� �������
//		Print(ms, n1);
//	}
//   Print(ms, n1);
//    free(ms);
//	return 0;
//}

//--------------------------------------------- 3 ------------------------------------

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int *ms, n1, i, j, k1, k2;
//	printf("������� ����������� ������� n1= ");
//	scanf("%d", &n1);
//	if (!n1) return 0;
//	if (!(ms = (int *)malloc(n1 * sizeof(int)))) { return 0; }
//
//	Vvod(ms, n1);
//	system("CLS");
//	Print(ms, n1);
//	printf("������� ������� ��������� ");
//	scanf("%d%d", &k1, &k2);
//	if (k1 > k2)
//	{
//		i = k1; k1 = k2; k2 = i;
//	}
//
//	while (k2 < n1) *(ms + k1++) = *(ms + k2++); // ���� ������ � �������
//	n1 -= k2 - k1;                               // ��������� ������� �������
//	ms = (int *)realloc(ms, sizeof(int)*n1); 
//		if (!ms) return 0;
//	Print(ms, n1);
//	free(ms);
//	return 0;
//}