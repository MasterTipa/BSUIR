#include<stdio.h>
#include<conio.h>
#include <locale.h>
#include <windows.h>
#include<stdlib.h>

//------------------------------     -----------------------------------------------
// ����������� ������ ������� ������� � �������
// ����� � ���������� ������

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
//	printf("������� ����� ������ ��������  = ");
//	scanf("%d", &n);
//	if ((str = (char *)malloc(n)) == nullptr)
//	{
//		puts("��� ��������� ������"); return 0;
//	}
//	system("CLS");	
//	printf("\n������� ������ ��������  ");
//	fflush(stdin);    // ������ �������� �������
//	gets(str);
//	printf("\n�������� ������  : %s", str);
//	i = 0;
//	while (*(str + i) == ' ') i++;  // ������� �������� ������� ������
//	i1 = i;                         // ������ ������� �����
//	while (*(str+i) && *(str + i) != ' ') i++;
//	i2 = i - 1;                     // ����� ������� �����
//	while (*(str + i) == ' ') i++;  // ������� �������� ������� ������
//	j1 = i;                         // ������ ������� �����
//	while (*(str + i) && *(str + i) != ' ') i++;
//	j2 = i - 1;                     // ����� ������� �����
//
//	swap(str + i1, str + j2);
//	swap(str + j2-(i2-i1), str + j2);
//	swap(str + i1, str + i1+(j2-j1));
//	printf("\n��������������� ������ : %s", str);
//	free(str);
//	return 0;
//}


//----------------------------------------------------------------------------------------------------
// ����� � �������� � ������ ����� MAX �����

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	char *st;
//	int i, i1, i2, i3, i4, size;
//	printf("������� ����� ������ ��������  = ");
//	scanf("%d", &size);
//	if(!(st = (char *)malloc(size)))
//	{
//		puts("��� ��������� ������"); return 0;
//	}
//	rewind(stdin);    // ������ �������� �������
//	gets(st);     // ���� ������ st1
//	system("CLS");
//	printf("\n�������� ������  : %s", st);
//	i = i3 = i4 = 0;
//	while (*(st + i))
//	{
//		while (*(st + i) == ' ') i++;
//		i1 = i;
//		while (*(st + i) != ' ' && *(st + i))  i++;
//		i2 = i - 1;
//		if (i2 - i1 + 1 > i4 - i3 + 1)  { i3 = i1; i4=i2; }
//	}
//	printf("\n����� max �����   : ");
//	for (i = i3; i<=i4; printf("%c", *(st + i++)));    // ����� ����� MAX �����
//	for (; *(st+i3)=*(st+i4+1); i3++,i4++);            // �������� ���������� �����
//	printf("\n��������������� ������  : %s", st);
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
		printf("������� ����������� ������ ������ = ");
	} while (!scanf("%d", &n1) || n1 <= 0);
	if (!(s1 = (char *)malloc(n1* sizeof(char))))
	{
		printf("\n������������ ��������� ������ \n");
		return 0;
	}
	do
	{
	    system("CLS"); 
		fflush(stdin);
		printf("������� ����������� ������ ������ = ");
	} while (!scanf("%d", &n2) || n2 <= 0);
	if (!(s2 = (char *)calloc(n2, sizeof(char))))
	{
		printf("\n������������ ��������� ������ \n");
		free(s1);
		return 0;
	}

	printf("������� ������ ������  ");
	fflush(stdin);
	printf("\n ������ %s", getstr(s1)); //����-����� ������ ������
	printf("\n����� ������ ������ == %d ����", str_len(s1));
	d = atof(s1);
	printf("\n�������� ����� (double) � ������ %s == %lf \n", s1, d);
	printf("\n����� ������ ������ == %d ����", get_str(s2, n2));
	printf("\n�������� ����� (int) � ������ %s == %d ", s2, atoi(s2));
	printf("\n������� ����� ��� �������� � ������  ");
	scanf("%d", &n);
	itoa(n, s2);
	printf("\n ������ %s", s2);
	if (str_cmp(s1, s2)>0) printf("\n������ 1 > ������ 2");
	else if (str_cmp(s1, s2)<0) printf("\n������ 1 < ������ 2");
	else printf("\n������ 1 = ������ 2");
	s1 = strcat(s1, s2, 3);
	printf("\n������ (s1+s2) == %s\n", s1);
	return 0;
}
// ������� �������� ���������� ������ � signed int
int atoi(char *ss)
{
	int n, i = 0, znak;
	while (ss[i] == ' ') i++;         // ������� �������� � ������ ������
	if (!ss[i]) return 0;             // � ������ ���� �������
	znak = (ss[i] == '-') ? -1 : 1;   // ���������� ���� �����
	if (ss[i] == '+' || ss[i] == '-') // ������� �����
		i++;
	for (n = 0; ss[i] >= '0' && ss[i] <= '9'; i++)  // ����� ���� ����� �� ������
		n = 10 * n + (ss[i] - '0');
	return znak*n;                    // ������� ����� �� ������
}

// ������� ����� ���� signed int � ���������� ������
void itoa(int n, char *ss)
{
	int i = 0, znak;
	if ((znak = n)<0)           // ��������� ����
		n *= -1;                // n- ������������� �����
	do                          // ����� ������� � ������ � �������� �������
	{
		ss[i++] = n % 10 + '0'; // ���������� ��������� ������ ������
	} while ((n /= 10)>0);      // ��������� ����� �� �����

	if (znak<0) ss[i++] = '-';
	ss[i] = '\0';               // ��������� ������� ����� ������
	for (n = 0; n<i / 2; n++)   // ������ (���������) ���������� ������
	{
		ss[n] += ss[i - 1 - n];
		ss[i - 1 - n] = ss[n] - ss[i - 1 - n];
		ss[n] -= ss[i - 1 - n];
	}
}

// ������� ��������� ���� �����
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2 && !(*s1 - *s2)) // ���� �� ��������� ����� ����� �� �����
		                               // � ���� ������� � ������� ���������
	{
		s1++;        // ����� � ������� ��������� ���� ��������
		s2++;
	}
	return *s1-*s2;  // >0 ���� ASCII-���  *s1 > *s2  ����� <0
}

//  -------------------------
//  for (;*s1==*s2; s1++,s2++)
//  if(*s1=='\0') return 0;
//  return *s1-*s2;
//  --------------------------

// ���� ������ � ������� �� ������
// get_str �� ��������� ���������� �������� ���� int
// � ss ���������� ��������� �� ������ ��� �����
int get_str(char *ss, int k)
{
	int c, i = 0;
	printf("\n������� ������ ������  ");
	// ������� ��������� � ����� � ����� ������� Enter k-1 ������
	// �� ������ ����������� � ������ ss
	while (--k>0 && (c = getchar()) != EOF && c != '\n')
		ss[i++] = c;   // ���� ������ �� ��������� ���-�� �������� ��� ����
	// �� ������ ������� Enter ��� Ctrl + Z
	ss[i] = '\0';
	return i;    // ������� ������ ������
}

// ���� ������
char *getstr(char *s)
{
	int i = 0;
	while ((*(s + i++) = (char)getchar()) != '\n');
	s[--i] = '\0';
	return s;    // ������� ������ ������
}

// ����������� ������ ������
int str_len(char *s)
{
	int t = 0;
	for (; s[t] != '\0'; t++);
	return t;
}

// ������� ������� / ���������� � ������ s1 ������ s2
// � ������� k
char * strcat(char *s1, char *s2, int k)
{
	char *s3;
	int i, n;
	if (k>str_len(s1)) k = str_len(s1);
	/*
	if ((s3=(char *)malloc(sizeof(char)*(str_len(s1)+str_len(s2))))==NULL)
	{ printf("\n������������ ��������� ������ ");
	return s1;                  // ������� ������ ��� ���������
	}
	for (i=0; i<k; i++)           // ���������� s1 � ss k ��������
	*(s3+i)=*(s1+i);
	for (i=0; *(s2+i); i++)       // �������� s2 � ss srt_len ��������
	*(s3+k+i)=*(s2+i);
	for (i=0; *(s1+k+i); i++)     // �������� ������� s1 � ss
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
// SetConsoleCP(1251);       // ��������� ������� �������� win-cp 1251 � ����� �����
// SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������
//unsigned char sm = '�';
//printf("%d ", sm);
//return 0;
/*************************************************************************************/

