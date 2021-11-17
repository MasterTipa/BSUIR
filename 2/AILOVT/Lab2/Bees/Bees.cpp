#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int input(FILE *);
void output(FILE*);
void krat(FILE*);
void cikl(FILE*,int);
int main()
{
	FILE* in,*out;
	int zn;
	if (!(fopen_s(&in, "input.bin", "rb+")) == NULL) exit(69);
	//if (!(fopen_s(&out, "output.bin", "wb+")) == NULL) exit(69);
	zn=input(in);
	//output(in);
	krat(in);
	cikl(in,zn);
	fclose(in);
	//fclose(out);
}
int input(FILE*in)
{
	int c;
	scanf_s("%d", &c);
	fseek(in,0,SEEK_SET);
	for (int i = 0;i < c;i++)
	{
		int d;
		scanf_s("%d", &d);
		fwrite(&d,sizeof(int),1,in);
	}
	return c;
};
void krat(FILE* in)
{
	int k,l,g=0;
	fseek(in,0,SEEK_SET);
	scanf_s("%d",&k);
	while (1)
	{
		fread(&l,sizeof(int),1,in);
		if (feof(in)) break;
		if (l % k == 0)g++;
		//printf("%d ",l);
		}
	printf("%d",g);
}
void cikl(FILE* in,int zn)
{
	int k,l,h,pzdc=sizeof(int);
	scanf_s("%d",&k);
	while (k>=zn*sizeof(int)) k-=zn*sizeof(int);
	if (k == 0) return;
	fseek(in,(-1*k),SEEK_END);
	fread(&h,k,1,in);
	fseek(in, (-2 * k), SEEK_END);
	while (zn > 0)
	{
		fread(&l,k,1,in);
		fwrite(&l, k, 1, in);
		fseek(in,(-2*pzdc)-k,SEEK_CUR);
		zn--;
	}
	fseek(in,0,SEEK_SET);
	fwrite(&h,k,1,in);
};
//void output(FILE* in)
//{
//	fseek(in,0,0);
//while(!feof(in))
//{
//	int d;
//		fscanf(in,"%d", &d);
//		printf( "%d ", d);
//	}
//};