#include <iostream>
int prb(char* s, int st)
{
	if ((*(s + st) >= 'a' && *(s + st) <= 'z') || (*(s + st) >= 'A' && *(s + st) <= 'Z')) return 1;
	else return 0;
}

int lengthw(char* s, int st)
{
	int zn = 0;
	while (prb(s,st)==0)
		st++;
	while (prb(s, st + zn) == 1)
		zn++;
	return zn;
}
int length(char ** s,int p) 
{
	int zn = 0;
	while (*(*(s + p) + zn) != '\n' && *(*(s + p) + zn) != '\0') zn++;
	return zn;
}

int main()
//{//1.	В строке найти все слова, которые начинаются с заданной буквы.
//
//	char* s = (char*)malloc(1 * sizeof(char));		char c;		int g = 0;
//
//	do {
//		c = getchar();
//		*(s + g++) = c;
//		s = (char*)realloc(s, (g + 1) * sizeof(char));
//	} while (c != '\n' && c != '\0');
//	int length = g;
//
//	scanf_s("%c", &c);
//
//	for (int i=0;i<length;i++)
//		if (i == 0 && *(s + i) == c) 
//		{
//			for (int j = 0;j < lengthw(s, i);j++)
//				printf("%c", *(s + j));
//			i += lengthw(s, i);
//			printf(" ");
//		}
//		else if (*(s + i) == c && prb(s, i - 1)==0)
//		{
//			for (int j = i;j < i+lengthw(s, i);j++)
//				printf("%c", *(s + j));
//			i += lengthw(s, i);
//			printf(" ");
//		}
//			
//
//
//}


{//2.	Из текста удалить все строки нечётной длины.
	int n = 5;
	char** s = (char**)malloc(n * sizeof(char*));		char c;		int g = 0;
	for (int i = 0;i < n;i++)
	{
		*(s + i) = (char*)malloc(1 * sizeof(char));
		do {
			c = getchar();
			*(*(s + i) + g++) = c;
			*(s + i) = (char*)realloc(*(s + i), (g + 1) * sizeof(char));
		} while (c != '\n' && c != '\0');
		//if (g % 2 != 0) { g = 0; *(s + i) = (char*)realloc(*(s + i), (g + 1) * sizeof(char)); i--;n--; 
	}
	
	for (int i = 0;i < n;i++)
	{for (int j = 0;j < length(s, i);j++)
		
			printf("%c", *(s + i) + j);
			printf("\n");
	}
}