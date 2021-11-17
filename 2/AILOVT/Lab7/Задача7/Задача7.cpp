//Организовать функции для ввода, вывода, поиска элемента в дереве.
//10. Создайте программой числовое двоичное дерево. Опишите рекурсивную логическую функцию,
//проверяющую наличие заданного числа в сформированном дереве. В программе используйте подпрограммы.
//Задание на 4 и на 7 похожи условием поиска, это же решается одной функцией.
//11. Напишите программу, содержащую функцию, которая строит Т1 – копию дерева Т. В программе используйте подпрограммы.
//Под словами подпрограмма, что именно вы подразумеваете?

#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
#include <locale.h>
struct tree
{
	int data;
	tree* left;
	tree* right;
};
void create(tree**,int);
void print(tree* );
int search(tree*,int);
void prt(tree*,tree**);
void zd10();
void zd11();
int main()
{
	setlocale(LC_ALL, "Russian");
	int gg;
	printf("Введите номер проверяемого задания (10 или 11) ");
	scanf_s("%d",&gg);
	if (gg == 10) zd10();
	else if (gg == 11) zd11();
	
}
void zd10() {
	tree* node = NULL;
	tree* node1 = NULL;
	int i;
	while (scanf("%d", &i))		//Использовал ваш ввод
		create(&node, i);
	rewind(stdin);
	print(node);
	printf("\n");
	printf("\nЧто вы хотите найти? ");
	scanf_s("%d", &i);
	search(node, i);
	printf("Нет\n");// Bool же нельзя использовать 
};
void zd11() {
	tree* node = NULL;
	tree* node1 = NULL;
	int i;
	while (scanf("%d", &i))		//Использовал ваш ввод
		create(&node, i);
	rewind(stdin);
	print(node);
	printf("\n");
	prt(node, &node1);
	print(node1);
};
void create(tree** node, int a) 
{
	tree* ptr;
	if (NULL == ((*node))) 
	{
		((*node)) = (tree*)calloc(1, sizeof(tree)); 
		((*node))->data = a; 
		((*node))->left = NULL;
		((*node))->right = NULL;
	}

	else if (a < ((*node))->data)  
	{
		if (((*node))->left != NULL) create(&((*node))->left, a);
		else 
		{
			((*node))->left = (tree*)calloc(1, sizeof(tree));  
			((*node))->left->left = ((*node))->left->right = NULL; 
			((*node))->left->data = a; 
		}
	}


	if (a > ((*node))->data)   
	{
		if (((*node))->right != NULL) create(&(*node)->right, a); 
		else 
		{
			((*node))->right = (tree*)calloc(1, sizeof(tree));  
			((*node))->right->left = ((*node))->right->right = NULL;
			((*node))->right->data = a; 
		}
	}
}
void print(tree* node) 
{
	if (node != NULL) 
	{
		/*printf("%4d ", node->data);
		print(node->left);
		printf("\n");
		print(node->right);*/
		printf("%4d ", node->data);print(node->left);print(node->right);
	}
}
int search(tree* node,int i)
{
	if (node->left != NULL)
		search(node->left, i);
	if (node->right != NULL)
		search(node->right, i);
	//printf("%d ",node->data);
	if (node->data == i) { printf("Есть");exit(0); }
	
}
void prt(tree* node, tree** node1)
{
	if (node != NULL)
	{
		create(node1, node->data);prt(node->left,node1);prt(node->right,node1);
	}
}