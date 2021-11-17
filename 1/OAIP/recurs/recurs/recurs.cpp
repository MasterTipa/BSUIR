#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>

//--------------------------------------------------------------------------------------
// ����������� �������r��� ���������� �����   n!
//int fact1(int);
//int fact2(int);
//int fact3(int);
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	system("CLS");
//	int n, i;
//	char c;
//	do
//	{
//		fflush(stdin);
//		puts("\n������� ����� >=0 ��� ���������� ��� ����-�� :");
//		i = scanf("%d", &n);
//	} while (i<1 || n<0);
//	printf("\n��������� ����� %d ( %d! ) = %d   ������� 1", n, n, fact1(n));
//	printf("\n��������� ����� %d ( %d! ) = %d   ������� 2", n, n, fact2(n));
//	printf("\n��������� ����� %d ( %d! ) = %d   ������� 3", n, n, fact3(n));
//	getch();
//}
//// ������� ���������� ����-��  (������� 1 )
//int fact1(int n)
//{
//	int i;
//	if (n == 1 || n == 0) return (1);    // ����� �� ��������
//	return fact1(n - 1)*n;
//}
//
//// ������� ���������� ����-��  (������� 2 )
//int fact2(int n)
//{
//	static long i; // i-����������� ����������, ����� ��������� ��� ���������
//	               // �������� ��� ������ ����� ������ ������� 
//	int factorial;
//	if (n <= 1)    // ���� ����� = 0 ��� 1
//		return 1;  // ��������� ����� 1    
//	if (++i < n)   // ���������� ��������������� ���������� i �� �������
//	{
//		factorial = i*fact2(n); // ������ �������� ������� ����������
//		i--;                    // �������������� i
//		return factorial;
//	}
//	i--;
//	return n;
//}
//
//// ������� ���������� ����-��  (������� 3 )
//int fact3(int n)
//{
//	return n>1 ? n*fact3(n - 1) : 1;
//}

//---------------------------------------------------------------------------------------------
// ����������� �������r��� ����� ������������� ����-��� ���������

//int fibon(int);
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	system("CLS");
//	int n, i;
//	printf("\n����� ��������� = ");
//	for (n = 0; n<15; n++) printf("%4d", fibon(n));
//	getch();
//}
//
//int fibon(int n)
//{
//	return ((n == 0 || n == 1)) ? 1 : fibon(n - 1) + fibon(n - 2);
//}

//-----------------------------------------------------------------------------------------------
// ����������� ��������� ������ �� �����
//
//# define kk 20
//void revers1(char *, int);
//void revers2(char *, int);
//
//// ����������� ����� ������
//int str_len(char *s)
//{
//	static int t;
//	if(s[t++]) str_len(s);
//	return t;
//}
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int nn;
//	char *st;
//	st = (char*)malloc(kk);
//	if(!st) return 0;
//	fflush(stdin);
//	puts("\n������� ���������� ������ : ");
//	gets(st);	
//	nn = str_len(st)-1;
//	system("CLS");
//	printf("\n nn=  %d", nn);
//	printf("\n������ �� ����������    %s", st);
//	revers2(st, nn);
//	printf("\n������ ����� ���������� %s", st);
//	revers2(st, nn);
//	printf("\n������ ����� ���������� %s", st);
//
//	getch();
//}
//
//// ����������� ������� ������������ ���������� ������
//void revers1(char *ss, int nn)
//{
//	static int i;
//	char c;
//	c = *(ss + i++);        // ��������� � ����� ��������� ��������� ������
//	if (c) revers1(ss, nn); // ����������� ����� ��� ���������� ������ ����.
//	else return;            // ���� �� ������ ����� ������, ����� ����� ��
//                          	// ��������
//	printf("\n i=  %d", i);
//	*(ss + nn - (--i)) = c; // �������� ������ �� �������� ����� ���������	
//	                        // ��������
//	if (i == 1) i = 0;
//}
//
//void revers2(char *ss, int nn)
//{
//	static int i;
//	char c;
//	c = *(ss + i);
//	*(ss + i) = *(ss + nn - 1 - i);       // ������ �������� �� ��� ��� ����
//	*(ss + nn - 1 - i++) = c;
//	if (i< (nn / 2)) revers2(ss, nn); // �� ���������� �������� ������
//	else return; 
//
//}

//----------------------------------------------------------------------------------
// ���������� ������� �����(������� �����)

#define k 9
void hoor(int *, int, int);
void swap(int *, int, int);
void FOR(int *, int, int, int, int &);

int main()
{
	setlocale(LC_ALL, "Russian");
	int a[k], i;

	puts("\n������� �������� ������� ");
	for (i = 0; i<k; i++)
	{
		fflush(stdin);
		if (!scanf("%d", &a[i])) i--;
	}
	system("CLS");
	printf("\n�������� ������        :");
	for (i = 0; i<k; i++) printf("%4d", a[i]);
	hoor(a, 0, k - 1);
	printf("\n\n��������������� ������ :");
	for (i = 0; i<k; i++) printf("%4d", a[i]);
	printf("\n");
}

void hoor(int *a, int l, int r)
{
	int i, las;
	if (l >= r)  return;
	swap(a, l, (l + r) / 2); // ������� ��-� ����������� � a[l] (a[l]<->a[(l+r)/2])
	las = l;                 // ������� ����-�� ��-�� �������� ��� �������
	for (i = l + 1; i <= r; i++) // ������� [l,r] �� [l,las-1] � [las+1,r]
	if (a[i]<a[l])                     
		swap(a, ++las, i);
	//FOR(a, l, r, 0, las);
	swap(a, l, las);
	hoor(a, l, las - 1);     // ���������� ��� [l,las-1]
	hoor(a, las + 1, r);     // ���������� ��� [las+1,r]
}

void swap(int *a, int i, int j)
{
	int tmp;                 // ������� ������ i � j ��-��� � ������� a
	tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}



// FOR(a,l,r,l,las);
void FOR(int *a, int l, int r, int i, int &las)
{ 
	if (i > r) return;
	if (a[i]<a[l])
		swap(a, ++las, i);
	FOR(a,l,r,++i,las);
}


