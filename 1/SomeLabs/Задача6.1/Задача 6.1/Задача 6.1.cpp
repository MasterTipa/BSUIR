#include <iostream>


int main()
//{
//	char* s = (char*)malloc(1 * sizeof(char));		char c;		int g = 0;
//	while ((c = getchar()) != '\n')
//	{
//		*(s + g++) = c;
//		s = (char*)realloc(s, (g + 1) * sizeof(char));
//	}
//	int length = g;
//	for (int i = 0;i < length - 1;i++)
//		for (int j = i + 1;j < length;j++)
//			if (*(s + i) == *(s + j))
//			{
//				while (j < length - 1)
//				{
//					char a = *(s + j + 1);
//					*(s + j + 1)= *(s + j);
//					*(s + j) = a;
//					j++;
//				}
//				s = (char*)realloc(s, (length) * sizeof(char));
//				length--;
//				i--;j = i+1;
//
//				for (int i = 0;i < length;i++)
//					printf("%c", *(s + i));
//				printf("\n");
//
//			}
//
//	for (int i = 0;i < length;i++)
//		printf("%c", *(s + i));
//
//
//}
{
	int m, n;
	char* s = (char*)malloc(1 * sizeof(char));		char c;		int g = 0;
		while ((c = getchar()) != '\n')
		{
			*(s + g++) = c;
			s = (char*)realloc(s, (g + 1) * sizeof(char));
		}
		int length = g;
		fflush(stdin);
		scanf_s("%d", &m);
		scanf_s("%d", &n);
		for (int i = 0;i < m;i++)
		{
			int j = 0;
			while (j < length - 1)
			{
				char a = *(s + j + 1);
				*(s + j + 1) = *(s + j);
				*(s + j) = a;
				j++;
			}
			s = (char*)realloc(s, (length) * sizeof(char));
			length--;
			i = 0;
			m--;n--;
		};
		for (int i =n;i < length;i++)
		{
			int j = n+1;
			while (j < length - 1)
			{
				char a = *(s + j + 1);
				*(s + j + 1) = *(s + j);
				*(s + j) = a;
				j++;
			}
			s = (char*)realloc(s, (length) * sizeof(char));
			length--;
			i = n;
			};

			for (int i = 0;i < length;i++)
				printf("%c", *(s + i));
		




}