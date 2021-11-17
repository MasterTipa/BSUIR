// 13.	Создать очередь для целых чисел. Максимальный размер очереди вводится с экрана. 
//Создать функции для ввода и вывода элементов очереди. 
//Ввести в очередь числа с экрана. После этого перейти в режим, 
//при котором при каждом вводе числа из очереди удаляется первый элемент, и если он 
//совпадает с введенным числом, то он добавляется в очередь.
//6.	Две днунаправленные очереди.В первой найти минимальный элемент которого нет во второй.
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include <windows.h>
struct queue {
	int data;
	struct queue* next;
};
struct queue2 {
	int data;
	struct queue2* next;
	struct queue2* prev;
};
struct queue* create(struct queue*,int);
struct queue2* create2(struct queue2*, int);
void print(struct queue*);
void print2(struct queue2*);
struct queue* pop(struct queue*);
struct queue2* pop2(struct queue2*);
void minq(struct queue2*, struct queue2*,int);
int pr(struct queue2*,int);
void zad13();
void zad6();
int main() {
	setlocale(LC_ALL, "Russian");
	printf("Введите номер проверяемого задания (13 или 6)");
	int x;
	scanf_s("%d", &x);
	if (x == 13) {
		zad13();
	}
	else 
		if (x == 6) {
			zad6();
		}
}
void zad6()
{
	int n;
	struct queue2* head1;	head1 = NULL;
	struct queue2* tail1;	tail1 = NULL;
	head1 = tail1;
	struct queue2* head2;	head2 = NULL;
	struct queue2* tail2;	tail2 = NULL;
	head2 = tail2;
	printf("Сколько элементов в 1-й очереди?");
	scanf_s("%d",&n);
	for (int i=0;i<n;i++){
		int x;	scanf_s("%d", &x);
		tail1 = create2(tail1, x);
		if (head1 == NULL)
			head1 = tail1;
	}
	printf("Сколько элементов в 2-й очереди?");
	scanf_s("%d", &n);
	for (int i = 0;i < n;i++) {
		int x;	scanf_s("%d", &x);
		tail2 = create2(tail2, x);
		if (head2 == NULL)
			head2 = tail2;
	}
	minq(head1,head2,999999);
	//print2(head1);
	//print2(head2);
	free(head1);
	free(head2);
}
void zad13()
{
	int n;
	struct queue* head;
	head = NULL;
	struct queue* tail;
	tail = NULL;
	head = tail;

	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x;	scanf_s("%d", &x);
		tail = create(tail, x);
		if (head == NULL)
			head = tail;
	}
	printf("\n");
	print(head);
	//Тут одна не точность. Не сказано до каких пор должен работать этот Режим. Я сделал, чтобы работало до тех пор, пока очередь не пустая.
	while (head != NULL)
	{
		int x;	scanf_s("%d", &x);
		if (x == head->data) tail = create(tail, x);
		head = pop(head);
		print(head);
	}
	free(head);
};
struct queue* create(struct queue* tail,int x) {
	struct queue* n = (struct queue*)malloc(sizeof(struct queue));
	n->next = NULL;		n->data = x;
	if (tail == NULL)	{tail = n;}
	else	{tail->next = n;tail = n;}
	return tail;
}
struct queue2* create2(struct queue2* tail, int x) {
	struct queue2* n;   
	n = (struct queue2*)malloc(sizeof(struct queue2));
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
void print(struct queue* head) {
	struct queue* p = head;
	while (p != NULL) {	printf("%d ", p->data);	p = p->next;}
	printf("\n");
}
void print2(struct queue2* head) {
	struct queue2* p = head;
	while (p != NULL) {    
		printf("%d ", p->data);
		p = p->next;   
	}
	printf("\n");
}
struct queue* pop(struct queue* head)
{
	if (head != NULL)
	{
		head = head->next;
		return head;
	}
	else return NULL;
}
void minq(struct queue2* head1, struct queue2* head2, int min)
{
	struct queue2* p = head1;
	while (p!=NULL)
	{
		if (p->data < min) { if (pr(head2,p->data)==1) min = p->data; }
		p = p->next;
	}
	if (min == 999999) printf("Таких чисел нет"); else printf("\n%d \n",min);
};
int pr(struct queue2* head,int x)
{
	struct queue2* p = head;
	while (p!=NULL)
	{
		if (x == p->data) return 0;
		p = p->next;
	}
	return 1;
};