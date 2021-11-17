#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>

//--------------------------------------------------------------------------------------
// Рекурсивное вычислеrние факториала числа   n!
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
//		puts("\nВводите число >=0 для вычисления его факт-ла :");
//		i = scanf("%d", &n);
//	} while (i<1 || n<0);
//	printf("\nФакториал числа %d ( %d! ) = %d   вариант 1", n, n, fact1(n));
//	printf("\nФакториал числа %d ( %d! ) = %d   вариант 2", n, n, fact2(n));
//	printf("\nФакториал числа %d ( %d! ) = %d   вариант 3", n, n, fact3(n));
//	getch();
//}
//// функция вычисления факт-ла  (вариант 1 )
//int fact1(int n)
//{
//	int i;
//	if (n == 1 || n == 0) return (1);    // выход из рекурсии
//	return fact1(n - 1)*n;
//}
//
//// функция вычисления факт-ла  (вариант 2 )
//int fact2(int n)
//{
//	static long i; // i-статическая переменная, чтобы сохранять своё последнее
//	               // значение при каждом новом вызове функции 
//	int factorial;
//	if (n <= 1)    // если число = 0 или 1
//		return 1;  // факториал равен 1    
//	if (++i < n)   // используем предварительное увеличение i на единицу
//	{
//		factorial = i*fact2(n); // заново вызываем функцию факториала
//		i--;                    // декрементируем i
//		return factorial;
//	}
//	i--;
//	return n;
//}
//
//// функция вычисления факт-ла  (вариант 3 )
//int fact3(int n)
//{
//	return n>1 ? n*fact3(n - 1) : 1;
//}

//---------------------------------------------------------------------------------------------
// Рекурсивное вычислеrние чисел принадлежащих посл-сти Фибоначчи

//int fibon(int);
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	system("CLS");
//	int n, i;
//	printf("\nЧисла Фибоначчи = ");
//	for (n = 0; n<15; n++) printf("%4d", fibon(n));
//	getch();
//}
//
//int fibon(int n)
//{
//	return ((n == 0 || n == 1)) ? 1 : fibon(n - 1) + fibon(n - 2);
//}

//-----------------------------------------------------------------------------------------------
// Рекурсивный переворот строки на месте
//
//# define kk 20
//void revers1(char *, int);
//void revers2(char *, int);
//
//// определение длины строки
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
//	puts("\nВводите символьную строку : ");
//	gets(st);	
//	nn = str_len(st)-1;
//	system("CLS");
//	printf("\n nn=  %d", nn);
//	printf("\nСтрока до переворота    %s", st);
//	revers2(st, nn);
//	printf("\nСтрока после переворота %s", st);
//	revers2(st, nn);
//	printf("\nСтрока после переворота %s", st);
//
//	getch();
//}
//
//// рекурсивные функции реверсивного переворота строки
//void revers1(char *ss, int nn)
//{
//	static int i;
//	char c;
//	c = *(ss + i++);        // сохраняем в стеке очередной считанный символ
//	if (c) revers1(ss, nn); // рекурсивный вызов для считывания нового симв.
//	else return;            // пока не считан конец строки, иначе выход из
//                          	// рекурсии
//	printf("\n i=  %d", i);
//	*(ss + nn - (--i)) = c; // обратный проход по функциям после окончания	
//	                        // рекурсии
//	if (i == 1) i = 0;
//}
//
//void revers2(char *ss, int nn)
//{
//	static int i;
//	char c;
//	c = *(ss + i);
//	*(ss + i) = *(ss + nn - 1 - i);       // замена символов до тех пор пока
//	*(ss + nn - 1 - i++) = c;
//	if (i< (nn / 2)) revers2(ss, nn); // не достигнута середина строки
//	else return; 
//
//}

//----------------------------------------------------------------------------------
// Сортировка массива чисел(методом Хоора)

#define k 9
void hoor(int *, int, int);
void swap(int *, int, int);
void FOR(int *, int, int, int, int &);

int main()
{
	setlocale(LC_ALL, "Russian");
	int a[k], i;

	puts("\nВводите элементы массива ");
	for (i = 0; i<k; i++)
	{
		fflush(stdin);
		if (!scanf("%d", &a[i])) i--;
	}
	system("CLS");
	printf("\nИсходный массив        :");
	for (i = 0; i<k; i++) printf("%4d", a[i]);
	hoor(a, 0, k - 1);
	printf("\n\nПреобразованный массив :");
	for (i = 0; i<k; i++) printf("%4d", a[i]);
	printf("\n");
}

void hoor(int *a, int l, int r)
{
	int i, las;
	if (l >= r)  return;
	swap(a, l, (l + r) / 2); // делящий эл-т переносится в a[l] (a[l]<->a[(l+r)/2])
	las = l;                 // позиция посл-го эл-та большего чем делящий
	for (i = l + 1; i <= r; i++) // деление [l,r] на [l,las-1] и [las+1,r]
	if (a[i]<a[l])                     
		swap(a, ++las, i);
	//FOR(a, l, r, 0, las);
	swap(a, l, las);
	hoor(a, l, las - 1);     // сортировка для [l,las-1]
	hoor(a, las + 1, r);     // сортировка для [las+1,r]
}

void swap(int *a, int i, int j)
{
	int tmp;                 // функция замены i и j эл-тов в массиве a
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


