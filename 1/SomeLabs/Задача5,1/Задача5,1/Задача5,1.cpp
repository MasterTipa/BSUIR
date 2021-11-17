#include <iostream>
void vvod(int* m, int n)
{
	for (int i = 0;i < n;i++)
		scanf_s("%d", (m + i));
};
void vivod(int* m, int n)
{
	for (int i = 0;i < n;i++)
		printf("%d ", *(m + i));
};
void swap(int* m, int i, int j)
{
	int t = *(m + i);
	*(m + i) = *(m + j);
	*(m + j) = t;
};
int max(int* m,int n)
{
	int max=*m;
	for (int i = 1;i < n;i++)
		if (*(m + i) > max) max = *(m + i);
	return max;
};
int min(int* m, int n)
{
	int min = *m;
	for (int i = 1;i < n;i++)
		if (*(m + i) < min) min = *(m + i);
	return min;
};
void Shell(int* a, int size)
{
	int step, i, j, tmp;
	for (step = size / 2; step > 0; step /= 2)
		for (i = step; i < size; i++)
			for (j = i - step; j >= 0 && *(a+j) > *(a+j + step); j -= step)
			{
				tmp = *(a+j);
				*(a+j) = *(a+j + step);
				*(a+j + step) = tmp;
			}
}
//int main()
//{ //1.	Отсортировать массив  в порядке убывания методом вставок
//	int n;
//	scanf_s("%d", &n);
//	int* m=(int*)malloc(n*sizeof(int));
//	vvod(m, n);
//	for (int i = 1;i < n;i++)
//	{
//		int j = i - 1, max = *(m+i);
//		while (j >= 0 && *(m+j) < max)
//		{
//			*(m+j + 1) = *(m+j);j--;
//		}
//		*(m+j + 1) = max;
//	}
//	
//	vivod(m, n);
//	
//
//}
//int main()
//{//1.	Выполнить сортировку четных элементов методом пузырька.
//	int n,g=0;
//	scanf_s("%d", &n);
//	int* m = (int*)malloc(n * sizeof(int));
//	vvod(m, n);
//	for (int i = 0;i < n - 1;i++)
//		for (int j = 0;j < n - g;j++)
//		{
//			g = 1;
//			if (*(m + j) % 2 == 0)
//			{
//				while (*(m + j + g) % 2 != 0 && g<n) g++;
//				if (*(m + j) < *(m + j + g) && g<n)
//				swap(m, j, j + g);
//			}
//		}
//	vivod(m, n);
//
//
//}
int main()
{//6.	Из двух упорядоченных одномерных массивов (длины K и N) сформируйте одномерный массив размером K+N, упорядоченный в обратную сторону.
	int n,k,i0=0,j0=0;
	scanf_s("%d", &n);
	int* m = (int*)malloc(n * sizeof(int));
		vvod(m, n);
	scanf_s("%d", &k);
	int*l = (int*)malloc(k * sizeof(int));
		vvod(l, k);
	int* s = (int*)malloc((k+n) * sizeof(int));
	Shell(m, n);Shell(l, k);
	for (int i = 0;i < k + n;i++)
		if (*(m + i0) < *(l + j0) && i0<n && j0<k) { *(s + i) = *(m + i0);i0++; }
		else if (j0<k) { *(s + i) = *(l + j0);j0++; }
		else { *(s + i) = *(m + i0);i0++; }
	printf("ms1 ");
	vivod(m, n);
	printf("\n");
	printf("ms2 ");
	vivod(l, k);
	printf("\n");
	printf("ms3 ");
	vivod(s, n + k);

}
