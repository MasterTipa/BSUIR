#include <stdio.h>
#include <locale.h>

//// ������ � ��������� ���� ��������� ����� �� �����������, 
//// �������� � ���� ������ �������� �� ��� ��������� ���������������
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	int a = 2, b = 3, c = 5, d=7;
//	int i, j;
//	fpos_t l1, l2;              // ��� ������� � �����
//	f = fopen("aaa", "w+");
//	fprintf(f,"%3d%3d%3d%3d",a,b,c,d);
//	while (1)
//	{
//		scanf("%d", &i);
//		if (i == 999) break;       // ����� �� ���������
//		rewind(f);	             // ��������� ���� � ������ ����� � �����
//		do                       // �������� ����� �����
//		{
//			fgetpos(f, &l1);        // ���� �������� ���� ������������ �����
//			fscanf(f, "%d", &j);
//			if (feof(f) || j>i)  break;
//		} while (1);
//		rewind(f);
//		if (j<i)                      // EOF � � ����� ��� ����� > ��� ��
//		{
//			fseek(f, 0, 2);               // ����� �� ����� �����
//			fprintf(f, "%3d", i);         // �������� � ����� �����
//			continue;
//		}
//		fseek(f, -3, 2);               // ���� �� ��������� ������� �����
//		do
//		{
//			fgetpos(f, &l2);            // ����� ���� ����� � ������� ��
//			fscanf(f, "%d", &j);      // l2 ������� ���� ����� ������� > ��� i
//			rewind(f);
//			l2 += 3;
//			fsetpos(f, &l2);
//			fprintf(f, "%3d", j);
//			fseek(f, l2 - 6, 0);
//		} while (l1<l2 - 3);
//		fseek(f, l2 - 3, 0);
//		fprintf(f, "%3d", i);    // ������ i �� ����� ����� � ���������
//	}	                         // ���������� ����� ���� ����� ����
//	fclose(f);
//}

// =====================================================================

// ������� 2 ����� ������������ �� �����������,
// ���������� �� � �������������� ��� ��������� ���������������

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f1, *f2, *f3;
//	int i1, i2;
//	int m1[] = { 1, 2, 4, 5 },
//		m2[] = { 1, 3 };
//	char cc;
//	if (!(f1 = fopen("a", "w+")) ||
//		!(f2 = fopen("aa", "w+")) ||
//		!(f3 = fopen("aaa", "w+")))
//	{
//		puts("error");
//		return 0;
//	}
//	for (i1 = 0; i1<sizeof(m1) / sizeof(int); i1++) fprintf(f1, "%d ", m1[i1]);
//	for (i1 = 0; i1<sizeof(m2) / sizeof(int); i1++) fprintf(f2, "%d ", m2[i1]);
//
//	rewind(f1); rewind(f2);
//	fscanf(f1, "%d", &i1);
//	fscanf(f2, "%d", &i2);
//	do
//	{	while (!feof(f1) && i1<i2)
//		{	fprintf(f3, "%d ", i1);
//			fscanf(f1, "%d", &i1);
//		}
//		if (feof(f1)) break;
//
//		while (!feof(f2) && i1 >= i2)
//		{	fprintf(f3, "%d ", i2);
//			fscanf(f2, "%d", &i2);
//		}
//	} while (!feof(f2));
//
//	while (!feof(f1))
//	{	fprintf(f3, "%d ", i1);
//		fscanf(f1, "%d", &i1);
//	}
//	while (!feof(f2))
//	{	fprintf(f3, "%d ", i2);
//		fscanf(f2, "%d", &i2);
//	}
//	fclose(f1);
//	fclose(f2);
//	rewind(f3);
//    while (1)
//    { fscanf(f3, "%d", &i1);
//	  if (feof(f3)) break;
//	  printf("%3d", i1);
//    }
//	printf("\n");
//	fclose(f3);
//	return 0;
//}


//============================================================================
// ������� 2 ����� ��� ����������� �� �����������,
// ���������� �� � �������������� ��� ��������� ���������������
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f1, *f2, *f3;
//	int i1, i2, j1, j2;
//	int m1[] = { 1, 2, 4, 5 },
//		m2[] = { 1, 3 };
//	char cc;
//	if (!(f1 = fopen("a", "w+")) ||
//		!(f2 = fopen("aa", "w+")) ||
//		!(f3 = fopen("aaa", "w+")))
//	{
//		puts("error");
//		return 0;
//	}
//	for (i1 = 0; i1<sizeof(m1) / sizeof(int); i1++) fprintf(f1, "%2d", m1[i1]);
//	for (i1 = 0; i1<sizeof(m2) / sizeof(int); i1++) fprintf(f2, "%2d", m2[i1]);
//
//	rewind(f1); rewind(f2);
//	j1 = fscanf(f1, "%d", &i1);
//	j2 = fscanf(f2, "%d", &i2);
//	do
//	{	while (i1<i2)
//		{	fprintf(f3, "%2d", i1);
//			if ((j1 = fscanf(f1, "%d", &i1)) == EOF) break;
//		}
//
//		while (i1 >= i2)
//		{	fprintf(f3, "%2d", i2);
//			if ((j2 = fscanf(f2, "%d", &i2)) == EOF) break;
//		}
//	} while (j1 != EOF && j2 != EOF);
//
//	if (j1 != EOF)
//	while (1)
//	{	fprintf(f3, "%2d", i1);
//		if (fscanf(f1, "%d", &i1) == EOF) break;
//	}
//	if (j2 != EOF)
//	while (1)
//	{	fprintf(f3, "%2d", i2);
//		if (fscanf(f2, "%d", &i2) == EOF) break;
//	}
//	fclose(f1);
//	fclose(f2);
//	rewind(f3);
//	while (1)
//	{	fscanf(f3, "%d", &i1);
//	    printf("%3d", i1);
//		if(feof(f3)) break;
//	}
//	
//	fclose(f3);
//  return 0;
//}

//============================================================================

// ������� 2 �����(aa - ���������� �� �����������, bb - �� ��������),
// ���������� �� � �������������� ���� �� �����������

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE *f1, *f2, *f3;
	int i1, i2, j1, j2;
	fpos_t n2;
	int m1[] = { 1, 2, 4, 5, 7},
		m2[] = { 3, 1 };
	if (!(f1 = fopen("aa", "w+")) ||
		!(f2 = fopen("bb", "w+")) ||
		!(f3 = fopen("cc", "w+")))
	{
		puts("error");
		return 0;
	}
	for (i1 = 0; i1<sizeof(m1) / sizeof(int); i1++) fprintf(f1, "%2d", m1[i1]);
	for (i1 = 0; i1<sizeof(m2) / sizeof(int); i1++) fprintf(f2, "%2d", m2[i1]);
	rewind(f1);
	fscanf(f1,"%d",&i1);    // ������ i1 � ������ ������� �����
	fseek(f2,-2,2);  
	fgetpos(f2,&n2);       
	fscanf(f2, "%d", &i2);           
	do
	{
		while(!feof(f1) && i1<i2)   // ��������� ��-� 1 ����� < ��� 2 �����
		{
			fprintf(f3,"%2d",i1);
			j1=fscanf(f1,"%d",&i1);
		}
		if(feof(f1) && i1<i2 && j1>0)
		{
			fprintf(f3,"%2d",i1);   // �������� ���������� �������� �� �����
			j1 = 0;                 // �������, ��� ��� ���������� �� ����� f1
			break;
		}
		while (n2>0 && i1>=i2)
		{
			fprintf(f3,"%2d",i2);
			n2-= 2;
			fsetpos(f2,&n2);
			j2=fscanf(f2,"%d",&i2);
		}
		if (n2<=0 && i1>=i2 && j2>0)  // ���������� ������ �����
		{
			fprintf(f3,"%2d",i2);     
			j2 = 0;
			break;
		}
	} while (!feof(f1) || n2>0);  
	
	if(j1>0) fprintf(f3, "%2d", i1);
	while (!feof(f1))                // 
	{	fscanf(f1,"%d",&i1);
		fprintf(f3,"%2d",i1);
	}
	if(j2>0) fprintf(f3, "%2d", i2);
	while (n2>0)
	{	n2-=2;
		fsetpos(f2,&n2);
		j2 = fscanf(f2,"%d",&i2);
		fprintf(f3,"%2d",i2);
	}
    fclose(f1);                   
	fclose(f2);
	rewind(f3);
	while (1)
	{
		fscanf(f3, "%d", &i1);
		printf("%3d", i1);
		if (feof(f3)) break;
	}
	fclose(f3);
	printf("\n");
	return 0;
}





























