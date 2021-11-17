#include <stdio.h>
#include <conio.h>
#include <locale.h>

//================================   union 1  ===========================================

	union u_tip {
		int i;
		float f;
		char s;
	} u;

int main()        
{
	u_tip u;
	setlocale(LC_ALL, "Russian");
	u.i = 1;
	/*u.f = 2.1;
	u.s = 'a';
*/
	printf("\n%d  ", sizeof(u));
	printf("\n%d  ", u.i);
	printf("\n%f  ", u.f);
	printf("\n%d  ", u.s);
	printf("\n%");
	return 0;
}



//================================   union 2  ===========================================

//#define k 2
//double f_var(int, ...);
//struct fg {
//	char name;
//	double s;
//	union {
//		struct {
//			int b;  // основание паралелограмма
//			int h;      // высота
//		} pr;
//		struct {
//			int b1, b2;  // основания трапеции
//			int h;      // высота
//		} tr;
//		struct {
//			int r;      // радиус окружности
//		} ok;
//	}f;
//};
//
//int main()         //
//{
//	struct fg un[k];
//	setlocale(LC_ALL, "Russian");
//	int i;
//	for (i = 0; i<k; i++)
//	{
//		puts("выберите фигуру для ввода    p   t   o");
//		fflush(stdin);
//		scanf("%c", &un[i].name);
//		switch (un[i].name)
//		{
//			case 'p': puts("введите основание и высоту пар-ма");
//				scanf("%d%d", &un[i].f.pr.b, &un[i].f.pr.h);
//				un[i].s = f_var(2, un[i].name, un[i].f.pr.b, un[i].f.pr.h);
//				break;
//			case 't': puts("введите 2 основания и высоту трапеции");
//				scanf("%d%d%d", &un[i].f.tr.b1, &un[i].f.tr.b2, &un[i].f.tr.h);
//				un[i].s = f_var(3, un[i].name, un[i].f.tr.b1, un[i].f.tr.b2, un[i].f.tr.h);
//				break;
//			case 'o': puts("введите радиус окружности");
//				scanf("%d", &un[i].f.ok.r);
//				un[i].s = f_var(1, un[i].name, un[i].f.ok.r);
//				break;
//		}
//	}
//	printf("\n%d  ", sizeof(un[i]));
//	for (i = 0; i<k; i++)
//	{
//		printf("\n площадь");
//		switch (un[i].name)
//		{
//	  	   case 'p': printf(" паралелограмма  = %5.2lf", un[i].s); break;
//		   case 't': printf(" трапеции        = %5.2lf", un[i].s); break;
//		   case 'o': printf(" окружности      = %5.2lf", un[i].s); break;
//		}
//	}
//	printf("\n%");
//	return 0;
//}
//
//double f_var(int kk, ...)
//{
//	void *p;
//	int i, s = 1;
//	char c;
//	p = (void*)&kk;
//	p=(int *)p+1;       // ++(int *)p;
//	c = *((char *)p);
//	p = (int *)p + 1;   // ((int *)p)++;
//	switch (c)
//	{
//		case 'p': 
//			for (i = 0; i < kk-1; i++)
//			{   
//			   s = s* *(int *)p;   p = (int *)p + 1;
//			}
//			break;
//		case 't': 
//			for (i = 0; i < kk-1; i++)
//		    {  
//		       s = s* *(int *)p;   p = (int *)p + 1;
//		    }	
//			s = s / 2 * *((int *)p);
//			break;
//		case 'o':
//			s = 3.14*(*((int *)p)* *((int *)p));
//			break;
//	}
//	return s;
//}

