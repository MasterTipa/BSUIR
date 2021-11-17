#include<stdio.h>
#include<conio.h>
#include <locale.h>
#include <windows.h>
#include<stdlib.h>

//------------------------------     -----------------------------------------------
// выполняется замена местами первого и второго
// слова в символьной строке
//void swap(char *s1,char *s2)
//{
//	char c;
//	for (; s1 < s2; s1++, s2--)
//	{ 
//		c = *s1; *s1 = *s2; *s2 = c;
//	}
//}
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	char *str, c;
//	int i, i1, i2, j, j1, j2, n;
//	printf("введите длину строки символов  = ");
//	scanf("%d", &n);
//	if ((str = (char *)malloc(n)) == nullptr)
//	{
//		puts("нет свободной памяти"); return 0;
//	}
//	system("CLS");	
//	printf("\nвведите строку символов  ");
//	fflush(stdin);    // чистка входного буффера
//	gets(str);
//	printf("\nИсходная строка  : %s", str);
//	i = 0;
//	while (*(str + i) == ' ') i++;  // пропуск пробелов вначале строки
//	i1 = i;                         // начало первого слова
//	while (*(str+i) && *(str + i) != ' ') i++;
//	i2 = i - 1;                     // конец первого слова
//	while (*(str + i) == ' ') i++;  // пропуск пробелов вначале строки
//	j1 = i;                         // начало второго слова
//	while (*(str + i) && *(str + i) != ' ') i++;
//	j2 = i - 1;                     // конец второго слова
//
//	swap(str + i1, str + j2);
//	swap(str + j2-(i2-i1), str + j2);
//	swap(str + i1, str + i1+(j2-j1));
//	printf("\nПреобразованная строка : %s", str);
//	free(str);
//	return 0;
//}


//----------------------------------------------------------------------------------------------------
// поиск и удаление в строке слова MAX длины
int main()
{
	setlocale(LC_ALL, "Russian");
	char *st;
	int i, i1, i2, i3, i4, size;
	printf("введите длину строки символов  = ");
	scanf("%d", &size);
	if(!(st = (char *)malloc(size)))
	{
		puts("нет свободной памяти"); return 0;
	}
	rewind(stdin);    // чистка входного буффера
	gets(st);     // ввод строки st1
	system("CLS");
	printf("\nИсходная строка  : %s", st);
	i = i3 = i4 = 0;
	while (*(st + i))
	{
		while (*(st + i) == ' ') i++;
		i1 = i;
		while (*(st + i) != ' ' && *(st + i))  i++;
		i2 = i - 1;
		if (i2 - i1 + 1 > i4 - i3 + 1)  { i3 = i1; i4=i2; }
	}
	printf("\nслово max длины   : ");
	for (i = i3; i<=i4; printf("%c", *(st + i++)));
	for (; *(st+i3)=*(st+i4+1); i3++,i4++);
	printf("\nПреобразованная строка  : %s", st);

}




