#include <iostream>
//void io(int* a,int n)
//{
//	int g;
//	scanf_s("%d", &g);
//	if (g != 0) {
//		n++; a = (int*)realloc(a, n * sizeof(int));
//		*(a + n - 1) = g;
//		io(a,n);
//		printf("%d ", *(a + n - 1));
//	};
//	
//}
//double par(int s, int h)
//{
//	return s * h;
//}
//double pir(int s, int h)
//{
//	return 1. / 3 * s * h;
//}
//double cil(int r, int h)
//{
//	return 3.14 * r * r * h;
//}
//double con(int r, int h)
//{
//	return 1. / 3 * r * r * 3.14 * h;
//}
//double(* func[])(int a, int c) = { par,pir,cil,con };
long int f1(long int i)
{
	long int j = i-1,g=1;
	while (j > 1) { g *= j; j--; }
	j = i + 1;
	printf("%d ", g);
	while (g > 1) { j *= j;g--; }
	return j;
}
long int f2(long int i)
{
	long int j = i - 1,g=i+1;
	if (j == 0) return g;
	else 
	{while (j > 1) { g *= g;j--; }
	return g;}
}
long int sum(long int i,long int s)
{
	if (i == 0) { return s; }
	else 
	{
		//printf("%d ", s);
		sum(i - 1, s + f1(i) / f2(i));
	}
}
int main()
//{
//	int n = 1;
//	int* ms = (int*)malloc(n * sizeof(int));
//	io(ms,n);
//}
//{
//	int s, h;
//	
//	scanf_s("%d%d", &s, &h);
//	for (int i = 0;i < 4;i++)
//		printf("%f ", func[i](s,h));
//	//printf("%f %f %f %f", par(s, h), pir(s, h), cil(s, h), con(s, h));
//
//
//
//
//}
{
	long int n;
	scanf_s("%d", &n);
	printf("%d", sum(n,0));
}