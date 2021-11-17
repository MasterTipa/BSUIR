#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <locale.h>

double f(double);
double pr(double(*)(double), double, double, double, int);
double tr(double(*)(double), double, double, double, int);

int main()
{	setlocale(LC_ALL, "Russian");
	double a, b, eps;
	int n;
	double(*ff)(double);
	puts("������� ������� a � b � �������� ���������� ��������� eps");
	scanf("%lf%lf%lf", &a, &b, &eps);
	puts("������� ������������ ����� �������� n");
	scanf("%d", &n);
	ff = f;
	printf("  �������� = %6.4lf\n", pr(ff, a, b, eps, n));
	printf("  �������� = %6.4lf\n", tr(ff, a, b, eps, n));
	return 0;
}

// ������������� ��������� �� ������� �� �������
// ���������� ��������� ������� " ��������������� "
double pr(double(*fi)(double), double a, double b, double e, int n)
{
	double y2 = 0.0, y1, x, h = (b - a) / n;
	do
	{
		y1 = y2; y2 = 0.0;
		for (x = a; x<b; x += h)
			y2 += (*fi)(x)*h;
		h /= 2;
	} while (fabs(y1 - y2)>e);
	return y2;
}

// ������������� ��������� �� ������� �� �������
// ���������� ��������� ������� " �������� "
double tr(double(*fi)(double), double a, double b, double e, int n)
{
	double y2 = 0, y1, x, h = (b - a) / n;
	do
	{
		y1 = y2;
		y2 = 0.5*((*fi)(a)+(*fi)(b));          //
		for (x = a + h; x<b; x += h) y2 += (*fi)(x);  //
		y2 *= h;
		h /= 2.0;
	} while (fabs(y1 - y2)>e);
	return y2;
}

double f(double x)
{
	return (x*x - 4.);       // ���������� �������� �-��� f(x)=x^2-4 � ����� �
}






// ������������� ��������� �� ������� �� �������
// ���������� ����� ����������� ��������� ������� " ����������� ������� "

//#include <stdio.h>
//#include <math.h>
//#include <conio.h>
//double f(double);
//double fun(double, double, double, double(*)(double));
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	double a, b, eps;
//	double(*ff)(double x);
//
//	puts("������� ������� a � b � �������� ���������� �����");
//	scanf("%lf%lf%lf", &a, &b, &eps);
//	ff = f;
//	printf("a= %5.2lf  b=%5.2lf  ������ = %6.4lf\n", a, b, fun(a, b, eps, ff));
//	getch();
//}
//double fun(double a, double b, double eps, double(*f1)(double))
//{
//	double fa, fb, c, fc;
//	do
//	{
//		fa = (*f1)(a);           // ���������� �������� ������� � ������
//		fb = (*f1)(b);           // ���������� ���������   [a,b]
//		c = (a + b) / 2.0;         // ������� ������� [a,b] �������
//		fc = (*f1)(c);         // �������� ������� � �������� �������
//		if (fa*fc>0) a = c;       //  ����� ������ [c,b]
//		else if (fb*fc>0) b = c;  //  ����� ������ [a,c]
//		else
//		{
//			puts("������ ������"); return c;
//		}
//	} while (fabs(a - b)>eps);  // ���� �� ���������� ��������  eps
//	return c;
//}
//
//double f(double x)
//{
//	return (x*x - 3.);       // ���������� �������� �-��� f(x)=x^2-3 � ����� �
//}                        // [ ���������� ����������� ������ �� 3 ]

//
//// ������������� ������� ���������� �� ������� �� �������
//// ����������� ����������� ����
//#include <stdio.h>
//#include <string.h>
//#include <conio.h>
//void funk1();
//void funk2();
//void funk3();
//void(*spisok[])() =        // ����������� � ���������������� 
//    {funk1, funk2, funk3}; // ������ ���������� �� �������
//int menu();
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int i;
//	puts("������ ������");
//	do
//	{
//		i = menu();              // ����� ������ �� ������
//		if (i<0 || i>2) break;
//		//spisok[i]();           // ����� i-�� ������� ����� ��������� �� ���
//		// (*spisok[i])();       // �����
//		// *spisok[i]();         // ������
//	} while (i >= 0 && i<3);
//	puts("��������� ������");
//}
//int menu()
//{
//	char c;
//	int i;
//	do
//	{
//		system("CLS");
//		puts("1    funk1");
//		puts("2    funk2");
//		puts("3    funk3");
//		puts("0    �����");
//		c = (char)getch();   // ����� ��� �������������� � char
//	} while (!strchr("0123", c));
//	return c - 49;           // ���������� ��������� �����
//}
//
//void funk1()
//{
//	puts("����������� �������   funk1");
//	getch();
//}
//void funk2()
//{
//	puts("����������� �������   funk2");
//	getch();
//}
//void funk3()
//{
//	puts("����������� �������   funk3");
//	getch();
//}
//
//
