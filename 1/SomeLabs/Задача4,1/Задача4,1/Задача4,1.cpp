#include <iostream>
#include <malloc.h>


//
//int main()
//{
//	int* mtr;
//	int m;
//	printf("m = ");
//	scanf_s("%d", &m);
//	mtr = (int*)calloc(m, sizeof(int));
//	for (int  i=0;i<m;i++)
//	scanf_s("%d",(mtr+i));
//	//for (int i = 0;i < m;i++)
//		//printf("%d ", *(mtr + i));
//	/*int** mtr;
//	int m=1,n=1;
//	mtr = (int**)calloc(m, sizeof(int*));
//	for (int i = 0;i < m;i++)
//		*(mtr + i) = (int*)calloc(n, sizeof(int));
//	for (int i=0;i<m;i++)
//	for (int j=0;j<n;j++)
//	scanf_s("%d",(*(mtr+i)+j));	
//	*/
//	for (int i = 0;i < m - 1;i++)
//	{
//		for (int j = i + 1;j < m;j++)
//			if (*(mtr + j) == *(mtr+i))
//			{
//				for (int g = j;g < m - 1;g++)
//					*(mtr + g) = *(mtr + g + 1);
//				m--;i--;
//				mtr = (int*)realloc(mtr, m * sizeof(int));
//			}
//
//	}
//	 
//	 for (int i = 0;i < m;i++)
//		 printf("%d ", *(mtr + i));
//
//}

//int main()
//{
//	int** mtr;
//	int m,n=0;
//	scanf_s("%d", &m);
//	mtr = (int**)malloc(m*sizeof(int*));
//	for (int i = 0;i < m;i++)
//	{
//		do {
//			n++;
//			if (n == 1)
//				*(mtr + i) = (int*)calloc(n , sizeof(int));
//			else *(mtr + i) = (int*)realloc(*(mtr+i), n * sizeof(int));
//			scanf_s("%d", (*(mtr + i) + n - 1));
//			
//		} 
//		while (*(*(mtr+i)+n-1) != -1);
//		for (int j=0;j<n;j++)
//			if (*(*(mtr + i) + j) < 0)
//			{
//				for (int g = j;g < n-1;g++)
//					*(*(mtr + i) + g) = *(*(mtr + i) + g + 1);
//				n--;j--;
//				*(mtr + i) = (int*)realloc(*(mtr + i), n * sizeof(int));
//			}
//				for (int j = 0;j < n;j++)
//			printf("%d ", *(*(mtr + i) + j));
//		n = 0;
//	}
//}
int main()
{
	int** mtr;
	int** mrt;
	int m, n ,k;
	scanf_s("%d%d%d", &m,&n,&k);
	mtr = (int**)malloc(m * sizeof(int*));
	mrt = (int**)malloc(m * sizeof(int*));
	for (int i = 0;i < m;i++)
	{
		*(mrt + i) = (int*)calloc(n, sizeof(int));
		*(mtr + i) = (int*)calloc(n, sizeof(int));
		for (int j = 0;j < n;j++)
		{
			scanf_s("%d", (*(mtr + i) + j));
			*(*(mrt + i) + j) = *(*(mtr + i) + j);
		}
	}
	while (k > n) { k -= n; }
	
	for (int i = 0;i < m;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (j - k >= 0) {
				*(*(mtr + i) + j - k) = *(*(mrt + i) + j);
			}
			else {
				*(*(mtr+i)+n-(k-j))= *(*(mrt + i) + j);
			}
		}
		
	}
	printf("\n");
	for(int i=0;i<m;i++)
	{
		for (int j = 0;j < n;j++)
			printf("%d ", *(*(mtr + i) + j));
		printf("\n");
	}

}
