#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stek {
	char inf;
	struct stek *next;
};
//В текстовом файле арифметическое выражение.
//Вывести его в другой файл в постфиксной форме.
//Использовать только стеки и массивы символов
struct stek* create(struct stek*, char);//добавление как у вас
void print(struct stek*);//вывод
struct stek* del(struct stek*);//удаление
int poisk(struct stek*);//поиск max

int main()
{
	char c;
	struct stek* head1;	struct stek* head2;
	head1 = NULL; head2 = NULL;

	FILE* F1, * F2;
	if (!(fopen_s(&F1, "F1.txt", "r")) == NULL) exit(69);
	if (!(fopen_s(&F2, "F2.txt", "w")) == NULL) exit(69);
	while (!feof(F1))
	{
		fscanf(F1,"%c",&c);
		if (c >= 'A' && c <= 'Z') { fprintf(F2,"%c",c); }
		else {
			head1 = create(head1, c);
			if (c == ')')
			{
				head1 = del(head1);
				while (c != '(' && head1 != NULL)
				{
					fprintf(F2, "%c", head1->inf);
					head1 = del(head1);
					c = head1->inf;
				}
				head1 = del(head1);

			}

		}
		}
	while (head1 != NULL)
	{
		//printf("%c", head2->inf);
		fprintf(F2, "%c", head1->inf);
		head1 = del(head1);
		//printf("%c", head1->inf);
		if (head1!=NULL)
		c = head1->inf;
	}
}
int poisk(struct stek* head)
{
	struct stek* m;
	m = (struct stek*)malloc(sizeof(struct stek));
	m = head;
	int z = 0;
	while (m != NULL) 
	{
		if (m->inf > z) { z = m->inf; };
		m = m->next;
	}
	return z;
};
struct stek *create(struct stek *head, char x) {
	struct stek *m;   
	m = (struct stek *)malloc(sizeof(struct stek)); 
	m->next = head;
	m->inf = x;
	return m;
}
void print(struct stek* head) {
	struct stek* m = head;
	while (m != NULL) {       
		printf("%c ", m->inf);
		m = m->next;      
	}
	printf("\n");
}//Вывод
struct stek* del(struct stek* head)
{
	//printf("GG");
	if (head != NULL)
	{
		head = head->next;
		return head;
	}
	else return NULL;

}