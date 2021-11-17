#include<stdio.h>
#include<conio.h>
#include <locale.h>
#include <windows.h>

//int mas1[20] = { 1, 2 };
//int main()
//{
//	extern int mas1[];  //   mas1[3] ошибка 'd' : redefinition; different subscripts
//	static int mas2[4];
//	int mas3[3] = { 1, 2 };
//	register int mas4[3] = { 1, 2, 3 };
//	//  int b[][2]={1,3,2};       //  {{1,3},{2,0}}
//	//  int b[][2]={{1},{3,2}};   //  {{1,0},{3,2}}
//	//  int b[][2]={{1},3,{2}};   //  {{1,0},{3,2}}
//	//  int b[][2]={1,3,{2}};     //  {{1,3},{2,0}}
//	//   int b[][2]={1,{3,2}};      // error
//	return 0;
//}


//--------------------------------------------- 2 -----------------------------------

//#define kl1 5        // объединение 2-х массивов в третий
//#define kl2 5
//
//void Vvod(int n, int MS[],int k)
//{
//	printf("введите значения в масив MS ");
//	if (n == 1) printf("по возрастанию\n");
//	else  printf("по убыванию\n");
//	int i = 0;
//	int j;
//	while (i < k)
//	{
//		printf("MS[ %d ] = ", i);
//		j=scanf("%d", &MS[i]);
//		if (j && (i == 0 || 
//			      (n == 1 && MS[i] >= MS[i - 1]) ||
//				  (n == 2 && MS[i] <= MS[i - 1]) ) ) i++;
//	}
//}
//
//void Print(int MS[], int k)
//{
//	printf("масив  : ");
//	for (int i = 0; i < k; i++)
//		printf("%4d", MS[i]);
//	printf("\n");
//}
//
//int main()
//{    
//	setlocale(LC_ALL, "Russian");
//	//const int kl1 = 5;
//	//const int kl2 = 5;
//	int X1[kl1], X2[kl2], X3[kl1+kl2], i1, i2, i3;
//	Vvod(1,X1,kl1);
//	system("CLS");                              
//	Vvod(1, X2, kl2);
//	system("CLS");                              
//	Print(X1,kl1);
//	Print(X2,kl2);
//
//	i1 = i2 = i3 = 0;
//	do
//	{
//		while (X1[i1] <= X2[i2] && i1<kl1) X3[i3++] = X1[i1++];
//		if (i1 >= kl1) break;
//		while (X1[i1]> X2[i2] && i2<kl2) X3[i3++] = X2[i2++];
//	} while (i1<kl1 && i2<kl2);
//	while (i1<kl1) X3[i3++] = X1[i1++];
//	while (i2<kl2) X3[i3++] = X2[i2++];
//
//	Print(X3, kl1+kl2);
//	printf("\n");
//	return 0;
//}

//--------------------------------------------- 1 ------------------------------------

//#define kl 5
//int main()                   // реверс элементов расположенных между MIN и MAX элементами
//{
//	setlocale(LC_ALL, "Russian");
//	system("CLS");                     // функция очистки консоли		
//	int MS[kl], i, i1, i2;
//	printf("введите значения в масив MS \n");
//	for (i = 0; i < kl; i++)           // цикл ввода элементов массива
//	{
//		printf("MS[ %d ] = ", i);
//		fflush(stdin);
//		// rewind(stdin);
//		if (!scanf("%d", &MS[i])) i--; // проверка на то, что введена не цифра
//	}
//	system("CLS");                      // функция очистки консоли		
//	printf("масив исходный        : "); // вывод введенного массива
//	for (int i = 0; i < kl; i++)
//		printf("%4d", MS[i]);
//	i1 = i2 = 0;                     // индекс MIN и MAX элементов массива
//	for (int i = 1; i < kl; i++)     // цикл поиска MIN и MAX
//	if (MS[i] < MS[i1]) i1 = i;      // индекс нового MIN
//	else if (MS[i] > MS[i2]) i2 = i; // индекс нового MAX
//	if (i1>i2)                       // i1 левее i2
//	{
//		i = i1; i1 = i2; i2 = i;     // замена значений i1 и i2
//	}
//	printf("\nMIN = %4d  MAX = %4d\n", MS[i1],MS[i2]);
//
//	for (; i1 < i2; i1++, i2--)       // цикл реверса элементов между i1 и i2
//	{
//		MS[i1] += MS[i2]; 
//		MS[i2] = MS[i1] - MS[i2]; 
//		MS[i1] -= MS[i2];
//	}
//	printf("масив преобразованный : "); // вывод преобразованного массива
//	for (int i = 0; i < kl; i++)
//		printf("%4d", MS[i]);
//	printf("\n");
//	return 0;
//}

//-------------------------------------------- 3 ---------------------------------

void Vvod(int[], int);
void Print(int[], int);
void Sort1(int, int []);
void Sort2(int, int []);
void Sort3(int, int []);
void shaker(int, int *);
void shell(int, int[]);

int main()                 
{
	setlocale(LC_ALL, "Russian");
	const int kl = 10;
	int mas[kl] = {4,2,6,1,2,7,3,1,1,5};
	//Vvod(mas,kl);
	system("CLS");           // функция очистки консоли  
	Print(mas,kl);           // вывод исходного массива
	printf("\nвыберите метод сортировки: 1-отбором\n");
	printf("выберите метод сортировки: 2-вставками\n");
	printf("выберите метод сортировки: 3-пузырьком\n");
	printf("выберите метод сортировки: 4-шейкер\n");
	printf("выберите метод сортировки: 5-Шелл\n");
	fflush(stdin);
	switch (getchar())
	{
	   case '1': Sort1(kl, mas); break;
	   case '2': Sort1(kl, mas); break;
	   case '3': Sort3(kl, mas); break;
       case '4': shaker(kl,mas); break;
	   case '5': shell(kl, mas); break;
	   default: printf("\nнеизвестный метод\n");
	}
	Print(mas, kl);           // вывод преобразованного массива
	printf("\n");
	getch();
	return 0;
}
void Vvod(int MS[],int k)
{
	printf("введите значения в масив MS ");
	int i = 0;
	int j;
	while (i < k)
	{
		printf("MS[ %d ] = ", i);
		j=scanf("%d", &MS[i]);
		if (j) i++;
	}
}

void Print(int MS[], int k)
{
	printf("масив  : ");
	for (int i = 0; i < k; i++)
		printf("%4d", MS[i]);
	printf("\n");
}
                            
void Sort1(int k, int ms[]) // сортировка массива  методом "через отбор"
{
	int i, j, m, kk;
	for (i = 0; i<k-1; ++i)
	{
		m = i;                    // индекс элемента для упорядочивания
		for (j = i + 1; j<k; ++j) // перебор последующих эл-тов справа от i-го
		if (ms[j]<ms[m])          // найден меньший
			m = j;                // запоминаем его индекс
		kk = ms[m];
		ms[m] = ms[i];            // замена выбранного и меньшего
		ms[i] = kk;
	}
}
      
void Sort2(int k, int ms[]) // сортировка чисел методом "вставок"
{
	int i, j, m;
	for (i = 1; i<k; ++i)         // индекс элемента для упорядочивания
	{
		j = i - 1;                // индекс предыдущего элемента
		m = ms[i];                // значение предыдущего элемента
		while (j >= 0 && m < ms[j])
		{
			ms[j-- + 1] = ms[j];  // сдвиг всех элементов направо
		} 
		ms[j + 1] = m;            // запись в освободившийся или в тот же элемент
	}
}
   
void Sort3(int k, int ms[]) // сортировка чисел методом "пузырька"
{
	int i, j, m;
	for (i = 0; i<k - 1; ++i)      // цикл kl-1 повтор (посл.эл-т не сорти-ся)
	for (j = k - 1; j>i; --j)
	{
		if (ms[j - 1] > ms[j])     // сравнение 2-х соседних элементов
		{                          // если правый < левого
			m = ms[j - 1];         // то замена их местами
			ms[j - 1] = ms[j];
			ms[j] = m;
		}
	}
}
// "Шейкер" сортировка чисел
void shaker(int kl, int *ms)
{ register int i,a,b,c,d;
   c=1;
   b=kl-1;   //номер элемента на котором остановка
   d=kl-1;   //номер стартового элемента для сортировки справа налево
   do
   { for(i=d;i>=c;--i)
     { if (ms[i-1]>ms[i])
       { a=ms[i-1];
	 ms[i-1]=ms[i];
	 ms[i]=a;
	 b=i;              // крайний слева упорядоченный элемент
       }
     }
     c=b+1;  //номер стартового элемента для сортировки слева направо
     for(i=c;i<=d;++i)
     { if (ms[i-1]>ms[i])
       { a=ms[i-1];
	 ms[i-1]=ms[i];
	 ms[i]=a;
	 b=i;              // крайний слева упорядоченный элемент
       }
     }
     d=b-1;
   } while(c<=d);
}

// "Шелл" сортировка чисел
void shell(int kl, int ms[])
{
	register int i, j, dp, a;
	//  dp=1;
	for (dp = kl / 2; dp>0; dp /= 2)
	for (i = dp; i<kl; i++)
	for (j = i - dp; j >= 0 && ms[j]>ms[j + dp]; j -= dp)
	{
		a = ms[j];
		ms[j] = ms[j + dp];
		ms[j + dp] = a;
	}
}
