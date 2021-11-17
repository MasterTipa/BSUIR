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

void Print(int MS[], int n, int k)   // MS[] и *MS  - эквивалентны  
{
	printf("масив  : ");
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
//	printf("введите размерность матрицы :");
//	printf("\nчисло строк = ");
//	if (!scanf("%d", &n)) return 0;
//	printf("\nчисло столбцов = ");
//	if (!scanf("%d", &m)) return 0;
//	if (!(mt= (int *)calloc(n*m, sizeof(int)))){ return 0; }
//
//	Vvod(mt,n,m);
//	system("CLS"); 
//	Print(mt,n,m);
//
//	p = mt;                 // указатель р на начало матрицы
//	do
//	{
//		printf("\nвыберите номер строки для подсчета суммы ее элементов : ");
//		rewind(stdin);
//	} while (!scanf("%d", &i) || (i >= m || i < 0));
//
//	p += i*m;               // указатель устанавливаем на начало строки i 
//	s = 0;                  // сумма элементов строки i 
//	for (i = 0; i<m; i++)   // перебор элементов строки 
//		s += *p++;          //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	printf("\nСумма элементов %d строки равна %d\n", n, s);
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
//void Print_float(float *MS, int n, int k)   // MS[] и *MS  - эквивалентны  
//{
//	printf("масив  : ");
//	for (int i = 0; i < n; i++)
//	{
//		printf("\n");
//		for (int j = 0; j < k; j++)
//			printf("%5.2f", *(MS + i*k + j));
//	}
//	printf("\n");
//}

//// выполнить сортировку элементов квадратной матрицы
//// расположенных выше побочной диагонали
//// используя указатель на матрицу
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int n, m, i, i1, j, j1, *p = nullptr, s;
//	float *mt;      // указатель для динамического выделения памяти под массив
//	float k;
//
//	printf("введите размерность матрицы :");
//	printf("\nчисло строк(столбцов) = ");
//	if (!scanf("%d", &n)) return 0;
//	m = n;                    // число ст-цов = числу строк 
//	if (!(mt = (float *)calloc(n*n, sizeof(float))))
//	{	puts("нет свободной памяти");
//		return 0;
//	}
//	Vvod_float(mt, n, m);
//	system("CLS");
//	printf("\nИсходная матрица\n ");
//	Print_float(mt, n, m);
//
//	for (i = 0; i < n - 2; i++)
//	for (j = 0; j < n - 1 - i; j++)         // выбор элемента для записи в него MIN
//	{
//		k = *(mt + i*n + j);                // исходное MIN значение
//		for (i1 = n - 2; i1 >= i; i1--)       // просмотр массива с конца (с последней стр.)
//		for (j1 = n - 2 - i1; j1 >= 0; j1--)  // c последнего элемента строки
//		if (mt + i*n + j < mt + i1*n + j1 &&  // выбранный адрес > исходого адреса
//			k>*(mt + i1*n + j1))              // и новое значение < исходного
//		{
//			k = *(mt + i1*n + j1);             // замена значений
//			*(mt + i1*n + j1) = *(mt + i*n + j);
//			*(mt + i*n + j) = k;
//		}
//	}
//	printf("\nПреобразованая матрица\n");
//	Print_float(mt, n, m);
//
//	free(mt);
//	return 0;
//}



//-----------------------------  3  -----------------------------------------
// пример работы с двухмерным массивом через указатель на указатель
// найти выше главной диагонали max ст-ц и ниже min
int main()
{
	setlocale(LC_ALL, "Russian");
	int **p, n, s, i, j, j1, j2, sum1, sum2, sum;
	do
	{
		system("CLS");
		printf("\nвведите размерность квадратной матрицы\n");
		i = scanf("%d", &n);
		if (i<1)
		{
			fflush(stdin);  // чистка буффера клавиатуры при ошибке ввода
			continue;       // повтор цикла do {}while
		}
		s = n;             // матрица квадратная
		if (!(p = (int **)malloc(sizeof(int*)*n)))
		{  printf("\nНедостаточно свободной памяти \nУуменьшите число строк массива");
		   continue;       // повтор цикла  do {}while
		}
		for (i = 0; i<n; i++)
		if (!(*(p + i) = (int *)malloc(sizeof(int)*s)))
		{
			printf("\nНедостаточно свободной памяти \nУуменьшите число ст-цов массива");
			for (j = 0; j<i; j++) free(*(p + j)); free(p);
			p = nullptr;   // сброс указателя для повтора
			break;
		}
	} while (!p);

	for (i = 0; i<n; i++)          // ввод массива
	for (j = 0; j<s; j++)
	{
		printf("Вводите элемент [%d][%d]= ", i, j);
		do
		{
			fflush(stdin);
		} while (!scanf("%d", *(p + i) + j));
	}
	
	system("CLS");
	printf("\nВведенный массив");
	for (i = 0; i<n; i++)          // вывод массива
	{
		printf("\n");
		for (j = 0; j<s; j++)
			printf("%3d", *(*(p + i) + j));
	}

	sum = 0;                         // контрольная сумма
	sum1 = *(*p + 1);                // для поиска max ст-ца выше диагонали
	sum2 = *(*(p + n - 1) + s - 2);  // для поиска min ст-ца ниже диагонали
	j1 = 1; j2 = s - 2;              // номера анализируемых ст-цов
	for (j = 0; j<s; j++)
	{
		for (i = 0; i<n; i++)
		if (i != j) sum += *(*(p + i) + j); // выбран для суммы не элемент диагонали
		else                                // выбран элемент диагонали
		{
			if (sum1<sum)         // найден ст-ц с большей суммой (над диагональю)
			{
				sum1 = sum;  j1 = j;   // запоминаем сумму и номер ст-ца
				sum = 0;               // сброс контрольной суммы 
			}
		}
		if (j<s - 1 && sum2>sum)  // найден ст-ц с меньшей суммой (под диагональю) 
		{
			sum2 = sum; j2 = j;       // запоминаем сумму и номер ст-ца
			sum = 0;                  // сброс контрольной суммы
		}
	}

	for (i = 0; i<n; i++)         // обнуление найденных ст-цов
	{
		if (i<j1) *(*(p + i) + j1) = 0;
		if (i>j2) *(*(p + i) + j2) = 0;
	}
	printf("\n\nПреобразованный массив");
	for (i = 0; i<n; i++)          // вывод массива
	{
		printf("\n");
		for (j = 0; j<s; j++)
			printf("%3d", *(*(p + i) + j));
	}
	for (i = 0; i<n; i++)  free(*(p + i));  free(p);
	getch();
}







