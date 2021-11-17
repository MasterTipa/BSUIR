//7.	Создать линейный однонаправленный список из целых чисел. Удалить из списка первый четный элемент, стоящий на нечетной позиции. 
//8.	Создать циклический двунаправленный список из целых чисел. Удалить из списка первый элемент со значением 10.
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include <windows.h>
void zd7();
void zd8();
struct lucic {
	int data;
	struct lucic* next;
	struct lucic* prev;
};
struct sps {
	int data;
	struct sps* next;
};
struct sps* create(struct sps*, int);
struct lucic* create2(struct lucic*, int);
struct sps* pop(struct sps*);
struct lucic* pops(struct lucic*);
void fuk(struct sps*);
struct lucic* fak(struct lucic*, int);
void print(struct sps* );
void print2(struct lucic*);
int schetchik(struct lucic*);
int main()
{
	setlocale(LC_ALL, "Russian");
	int x;
	printf("Введите номер проверяемого задания (7 или 8) ");
	scanf_s("%d", &x);
	if (x == 7) {zd7();	}
	else
	if (x == 8) {zd8();	}
}
void zd7() {
	int n;
	printf("Сколько элементов в списке ");
	struct sps* head;	head = NULL;
	struct sps* tail;	tail = NULL;	head = tail;
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x;	scanf_s("%d", &x);
		tail = create(tail, x);
		if (head == NULL)	head = tail;
	}
	fuk(head);//Данная функция выполняет удаление первого чётного элемента, стоящего на нечетной позиции
	free(head);free(tail);
};
void zd8() 
{ 
	int n;
	printf("Сколько элементов в списке ");
	struct lucic* head;	head = NULL;
	struct lucic* tail;	tail = NULL;
	head = tail;
	scanf_s("%d", &n);
	for (int i = 0;i < n;i++) {
		int x;	scanf_s("%d", &x);
		tail = create2(tail, x);
		if (head == NULL)
			head = tail;
	}
	tail->next = head;
	head->prev = tail;
	head=fak(head,n);
	print2(head);
	free(head);free(tail);
};
void fuk(struct sps* head)
{
	struct sps* p = head;
	int m=1;
	while (p != NULL && !(p->data % 2 == 0 && m % 2 == 1))
	{
		printf("%d ", p->data);
		p = p->next;m++;
	}
	p = pop(p);
	print(p);
};
struct lucic* fak(struct lucic* head, int n)
{
	while (n != 0)
	{
		if (head->data == 10)
		{
			head = head->prev;
			head->next = head->next->next;
			return head;
		}
		n--;
		struct lucic* m;
		m = (struct lucic*)malloc(sizeof(struct lucic));
		m = head;head = head->next;head->prev = m;
	};
	return head;
}
struct sps* create(struct sps* tail, int x) {
	struct sps* n = (struct sps*)malloc(sizeof(struct sps));
	n->next = NULL;		n->data = x;
	if (tail == NULL) { tail = n; }
	else { tail->next = n;tail = n; }
	return tail;
}
struct lucic* create2(struct lucic* tail, int x) {
	struct lucic* n;
	n = (struct lucic*)malloc(sizeof(struct lucic));
	n->next = NULL;
	n->prev = NULL;
	n->data = x;
	if (tail == NULL)
	{
		tail = n;
	}
	else
	{
		n->prev = tail;
		tail->next = n;
		tail = n;
	}
	return tail;
}
struct sps* pop(struct sps* head)
{
	if (head != NULL)
	{
		head = head->next;
		return head;
	}
	else return NULL;
}
void print(struct sps* head) {
	struct sps* p = head;
	while (p != NULL) { printf("%d ", p->data);	p = p->next; }
	printf("\n");
}
void print2(struct lucic* head) 
{
	int gg = schetchik(head);
	struct lucic* p = head;
	while (p != NULL && gg != 0) {
		gg--;
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
int schetchik(struct lucic* head)
{
	struct lucic* p = head->next;
	int lol = 1;
	while (p != head) { lol++;p = p->next; }
	return lol;
};