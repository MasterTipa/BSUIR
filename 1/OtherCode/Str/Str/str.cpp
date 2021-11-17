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

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	char *st;
//	int i, i1, i2, i3, i4, size;
//	printf("введите длину строки символов  = ");
//	scanf("%d", &size);
//	if(!(st = (char *)malloc(size)))
//	{
//		puts("нет свободной памяти"); return 0;
//	}
//	rewind(stdin);    // чистка входного буффера
//	gets(st);     // ввод строки st1
//	system("CLS");
//	printf("\nИсходная строка  : %s", st);
//	i = i3 = i4 = 0;
//	while (*(st + i))
//	{
//		while (*(st + i) == ' ') i++;
//		i1 = i;
//		while (*(st + i) != ' ' && *(st + i))  i++;
//		i2 = i - 1;
//		if (i2 - i1 + 1 > i4 - i3 + 1)  { i3 = i1; i4=i2; }
//	}
//	printf("\nслово max длины   : ");
//	for (i = i3; i<=i4; printf("%c", *(st + i++)));    // вывод слова MAX длины
//	for (; *(st+i3)=*(st+i4+1); i3++,i4++);            // удаление найденного слова
//	printf("\nПреобразованная строка  : %s", st);
//
//}

int atoi(char *);
void itoa(int, char *);
int str_cmp(char *, char *);
int get_str(char *, int);
char *getstr(char *);
int str_len(char *);
char *strcat(char *, char *, int);

int main()
{
	setlocale(LC_ALL, "Russian");	
	char *s1, *s2;
    unsigned int n, n1, n2;
	double d;
	
	do
	{
		system("CLS");
		fflush(stdin);
		printf("введите размерность ПЕРВОЙ строки = ");
	} while (!scanf("%d", &n1) || n1 <= 0);
	if (!(s1 = (char *)malloc(n1* sizeof(char))))
	{
		printf("\nНедостаточно свободной памяти \n");
		return 0;
	}
	do
	{
	    system("CLS"); 
		fflush(stdin);
		printf("введите размерность ВТОРОЙ строки = ");
	} while (!scanf("%d", &n2) || n2 <= 0);
	if (!(s2 = (char *)calloc(n2, sizeof(char))))
	{
		printf("\nНедостаточно свободной памяти \n");
		free(s1);
		return 0;
	}

	printf("Вводите первую строку  ");
	fflush(stdin);
	printf("\n строка %s", getstr(s1)); //ввод-вывод первой строки
	printf("\nДлина первой строки == %d байт", str_len(s1));
	d = atof(s1);
	printf("\nЗначение числа (double) в строке %s == %lf \n", s1, d);
	printf("\nДлина второй строки == %d байт", get_str(s2, n2));
	printf("\nЗначение числа (int) в строке %s == %d ", s2, atoi(s2));
	printf("\nВводите число для перевода в строку  ");
	scanf("%d", &n);
	itoa(n, s2);
	printf("\n строка %s", s2);
	if (str_cmp(s1, s2)>0) printf("\nСтрока 1 > строки 2");
	else if (str_cmp(s1, s2)<0) printf("\nСтрока 1 < строки 2");
	else printf("\nСтрока 1 = строке 2");
	s1 = strcat(s1, s2, 3);
	printf("\nстрока (s1+s2) == %s\n", s1);
	return 0;
}
// перевод цифровой символьной строки в signed int
int atoi(char *ss)
{
	int n, i = 0, znak;
	while (ss[i] == ' ') i++;         // пропуск пробелов в начале строки
	if (!ss[i]) return 0;             // в строке одни пробелы
	znak = (ss[i] == '-') ? -1 : 1;   // запоминаем знак числа
	if (ss[i] == '+' || ss[i] == '-') // пропуск знака
		i++;
	for (n = 0; ss[i] >= '0' && ss[i] <= '9'; i++)  // выбор цифр числа из строки
		n = 10 * n + (ss[i] - '0');
	return znak*n;                    // возврат числа со знаком
}

// перевод числа типа signed int в символьную строку
void itoa(int n, char *ss)
{
	int i = 0, znak;
	if ((znak = n)<0)           // сохраняем знак
		n *= -1;                // n- положительное число
	do                          // цифры заносим в строку в обратном порядке
	{
		ss[i++] = n % 10 + '0'; // выделяется последний справа разряд
	} while ((n /= 10)>0);      // удаляется цифра из числа

	if (znak<0) ss[i++] = '-';
	ss[i] = '\0';               // заносится признак конца строки
	for (n = 0; n<i / 2; n++)   // реверс (переворот) полученной строки
	{
		ss[n] += ss[i - 1 - n];
		ss[i - 1 - n] = ss[n] - ss[i - 1 - n];
		ss[n] -= ss[i - 1 - n];
	}
}

// функция сравнения двух строк
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2 && !(*s1 - *s2)) // пока не достигнут конец одной из строк
		                               // и пока символы в строках совпадают
	{
		s1++;        // выбор к анализу следующей пары символов
		s2++;
	}
	return *s1-*s2;  // >0 если ASCII-код  *s1 > *s2  иначе <0
}

//  -------------------------
//  for (;*s1==*s2; s1++,s2++)
//  if(*s1=='\0') return 0;
//  return *s1-*s2;
//  --------------------------

// ввод строки и подсчет ее длинны
// get_str по умолчанию возвращает значение типа int
// в ss копируется указатель на строку для ввода
int get_str(char *ss, int k)
{
	int c, i = 0;
	printf("\nВводите вторую строку  ");
	// символы заносятся в буфер и после нажатия Enter k-1 символ
	// из буфера переносятся в строку ss
	while (--k>0 && (c = getchar()) != EOF && c != '\n')
		ss[i++] = c;   // ввод строки до заданного кол-ва символов или пока
	// не нажата клавиша Enter или Ctrl + Z
	ss[i] = '\0';
	return i;    // возврат длинны строки
}

// ввод строки
char *getstr(char *s)
{
	int i = 0;
	while ((*(s + i++) = (char)getchar()) != '\n');
	s[--i] = '\0';
	return s;    // возврат длинны строки
}

// определение длинны строки
int str_len(char *s)
{
	int t = 0;
	for (; s[t] != '\0'; t++);
	return t;
}

// функция вставки / добавления в строку s1 строки s2
// с позиции k
char * strcat(char *s1, char *s2, int k)
{
	char *s3;
	int i, n;
	if (k>str_len(s1)) k = str_len(s1);
	/*
	if ((s3=(char *)malloc(sizeof(char)*(str_len(s1)+str_len(s2))))==NULL)
	{ printf("\nНедостаточно свободной памяти ");
	return s1;                  // возврат строки без изменения
	}
	for (i=0; i<k; i++)           // перезапись s1 в ss k символов
	*(s3+i)=*(s1+i);
	for (i=0; *(s2+i); i++)       // дозапись s2 в ss srt_len символов
	*(s3+k+i)=*(s2+i);
	for (i=0; *(s1+k+i); i++)     // дозапись остатка s1 в ss
	*(s3+k+str_len(s2)+i)=*(s1+k+i);
	*(s3+k+str_len(s2)+i)='\0';
	free(s1);
	return s3;
	*/

	s1 = (char*)realloc(s1, str_len(s1) + str_len(s2) + 1);
	for (i = str_len(s1); i >= k; i--)
		*(s1 + i + str_len(s2)) = *(s1 + i);
	for (i = 0; i<str_len(s2); i++)
		*(s1 + k + i) = *(s2 + i);

	return s1;
}










/*************************************************************************************/
// SetConsoleCP(1251);       // установка кодовой страницы win-cp 1251 в поток ввода
// SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
//unsigned char sm = 'а';
//printf("%d ", sm);
//return 0;
/*************************************************************************************/

