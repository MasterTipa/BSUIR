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


//---------------------------------------------   1  -----------------------------------

#define nstr 3
#define nstl 4

void Vvod(int MT[][nstl],int str,int stl)
{
	printf("введите значения в матрицу MT\n");
	int i, j;
	for (i = 0; i < str; i++)
	for (j = 0; j < stl; j++)
	{
		fflush(stdin);
		printf("MT[ %d ][ %d ] = ", i,j);
		if (!scanf("%d", &MT[i][j])) j--;
	}
}

void Print(int MT[][nstl], int str, int stl)
{
	printf("\nматрица MT\n");
	int i, j;
	for (i = 0; i < str; i++)
	{
		printf("\n");
		for (j = 0; j < stl; j++)
			printf("%4d", MT[i][j]);
	}
	printf("\n");
}

//int main()
//{    
//	setlocale(LC_ALL, "Russian");
//	//const int kl1 = 5;
//	//const int kl2 = 5;
//	int MT[nstr][nstl], i1, i2, i3;
//	Vvod(MT,3,3);    // ввод матрицы [3][3]
//	system("CLS");                              
//	Print(MT,3,3);   // вывод исходной матрицы
//
//	//   операторы работы с матрицей 
//
//	Print(MT, 3, 3);   // вывод преобразованной матрицы
//	printf("\n");
//	return 0;
//}


//---------------------------------------------   2  ------------------------------------
//  Транспонировать матрицу относительно главной диагонали

//int main()                   
//{
//	setlocale(LC_ALL, "Russian");		
//    int mtr[nstr][nstl], i, j, kk;
//	const int n1 = 3;
//	const int n2 = 3;
//	Vvod(mtr,3,3);    // ввод матрицы [3][3]
//	system("CLS");  
//	printf("\nИсходная матрица");   
//	Print(mtr,3,3);   // вывод исходной матрицы
//	//************* использован цикл  for(){...}
//	for(i=0;i<n1;i++)    
//	for(j=i+1;j<n2;j++)
//	{ kk=mtr[i][j];
//	  mtr[i][j]=mtr[j][i];
//	  mtr[j][i]=kk;
//	}
//	/**************/
//	/************* использован цикл   do{...}while()
//	i=0;
//	do
//	{ j=i+1;
//	  do
//	  { kk=mtr[i][j];
//    	mtr[i][j]=mtr[j][i];
//	    mtr[j][i]=kk;
//	    j++;
//	  }while(j<n2);
//	  i++;
//	}while(i<n1);
//	**************/
//    /************* использован цикл   while(){...}
//	i = 0;
//	while (i<n1)
//	{	j = i + 1;
//	    while (j<n2)
//		{	kk = mtr[i][j];
//	        mtr[i][j] = mtr[j][i];
//			mtr[j][i] = kk;
//			j++;
//		};
//		i++;
//	};
//   ************/
//    printf("\nТранспонированная матрица");
//	Print(mtr, 3, 3);   // вывод исходной матрицы
//	printf("\n");
//	return 0;
//}



//---------------------------------------------   3  ------------------------------------
// нахождение седловой точки двухмерного массива
// (наибольшую в строке и наименьшую в столбце)

int main()
{    
	setlocale(LC_ALL, "Russian");
	int mt[nstr][nstl], i, i1, i2, j, j1, k, kk;
	Vvod(mt, nstr, nstl);    // ввод матрицы [3][3]
	system("CLS");                              
	Print(mt, nstr, nstl);   // вывод исходной матрицы

	//поиск седловой точки
	for (i = 0; i<nstr; i++)
	{
		k = mt[i][0]; i1 = 0; j1 = 0;  // начальное значениеи координата
	                                   // для выбора седловой точки
		for (j = 0; j<nstl; j++)
		if (mt[i][j]>k)
		{
			k = mt[i][j];    // запоминаем новое значение для поиска седл.тчк.
			i1 = i; j1 = j;  //  и ее координаты в матрице
		}
		kk = 0;
		for (i2 = 0; i2<nstr; i2++)
		if (mt[i1][j1] >= mt[i2][j1] && i1 != i2) kk = 1;
		if (kk == 0)
			printf("\nседловая точка = %d  \nкоординаты : mt[%d][%d] ", mt[i1][j1], i1, j1);
	}
	printf("\n");
	return 0;
}

