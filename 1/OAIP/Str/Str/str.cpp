#include<stdio.h>
#include<conio.h>
#include <locale.h>
#include <windows.h>
#include<stdlib.h>

//------------------------------     -----------------------------------------------
// ����������� ������ ������� ������� � �������
// ����� � ���������� ������
//void swap(char *s1,char *s2)
//{
//	char c;
//	for (; s1 < s2; s1++, s2--)
//	{ 
//		c = *s1; *s1 = *s2; *s2 = c;
//	}
//}
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	char *str, c;
//	int i, i1, i2, j, j1, j2, n;
//	printf("������� ����� ������ ��������  = ");
//	scanf("%d", &n);
//	if ((str = (char *)malloc(n)) == nullptr)
//	{
//		puts("��� ��������� ������"); return 0;
//	}
//	system("CLS");	
//	printf("\n������� ������ ��������  ");
//	fflush(stdin);    // ������ �������� �������
//	gets(str);
//	printf("\n�������� ������  : %s", str);
//	i = 0;
//	while (*(str + i) == ' ') i++;  // ������� �������� ������� ������
//	i1 = i;                         // ������ ������� �����
//	while (*(str+i) && *(str + i) != ' ') i++;
//	i2 = i - 1;                     // ����� ������� �����
//	while (*(str + i) == ' ') i++;  // ������� �������� ������� ������
//	j1 = i;                         // ������ ������� �����
//	while (*(str + i) && *(str + i) != ' ') i++;
//	j2 = i - 1;                     // ����� ������� �����
//
//	swap(str + i1, str + j2);
//	swap(str + j2-(i2-i1), str + j2);
//	swap(str + i1, str + i1+(j2-j1));
//	printf("\n��������������� ������ : %s", str);
//	free(str);
//	return 0;
//}


//----------------------------------------------------------------------------------------------------
// ����� � �������� � ������ ����� MAX �����
int main()
{
	setlocale(LC_ALL, "Russian");
	char *st;
	int i, i1, i2, i3, i4, size;
	printf("������� ����� ������ ��������  = ");
	scanf("%d", &size);
	if(!(st = (char *)malloc(size)))
	{
		puts("��� ��������� ������"); return 0;
	}
	rewind(stdin);    // ������ �������� �������
	gets(st);     // ���� ������ st1
	system("CLS");
	printf("\n�������� ������  : %s", st);
	i = i3 = i4 = 0;
	while (*(st + i))
	{
		while (*(st + i) == ' ') i++;
		i1 = i;
		while (*(st + i) != ' ' && *(st + i))  i++;
		i2 = i - 1;
		if (i2 - i1 + 1 > i4 - i3 + 1)  { i3 = i1; i4=i2; }
	}
	printf("\n����� max �����   : ");
	for (i = i3; i<=i4; printf("%c", *(st + i++)));
	for (; *(st+i3)=*(st+i4+1); i3++,i4++);
	printf("\n��������������� ������  : %s", st);

}




