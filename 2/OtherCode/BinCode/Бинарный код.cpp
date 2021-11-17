#include <iostream>
#include <stdio.h>
int main()
{
	FILE* in;
	if ((in = fopen_s("D:\\Бинарный код\input.txt", "r+b")) == NULL)
	{exit(1);}




	fclose(in);
}