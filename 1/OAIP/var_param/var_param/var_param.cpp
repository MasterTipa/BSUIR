// ������� ���������� ������� � ���������� ������ ����������
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>



//void fun1(int, ...);    // �������� �-��� ������� 1 ���������� ��������
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	long int b1, b2;
//	long long int c1, c2, c3, c4;
//	int a1, a2, a3;
//	printf("%d\n", sizeof(char));
//	printf("%d\n", sizeof(short int));	
//	printf("%d\n", sizeof(int));
//	printf("%d\n", sizeof(long int));
//	printf("%d\n", sizeof(long long int));
//	puts("������� 3 int :");
//	scanf("%d%d%d", &a1, &a2, &a3);
//	puts("������� 2 long int :");
//	scanf("%ld%ld", &b1, &b2);
//	puts("������� 4 long long int :");
//	scanf("%ld%ld%ld%ld", &c1, &c2, &c3, &c4);
//	fflush(stdin);
//	fun1(3, a1, a2, a3);
//	fun1(2, b1, b2);
//	fun1(4, (long int)c1, (long int)c2, (long int)c3, (long int)c4);
//	fun1(2, '1', '2');
//	return 0;
//}
//
//void fun1(int k, ...)
//{
//	int s = 0;
//	void *p;
//	p = &k;                  // p ��������� �� ������� ����� k
//	p = ((int *)p) + 1;      // ��������� �� ��������� ������� �����
//	while (k--) 
//	{  s += *((int *)p); 
//       p = ((int *)p) + 1; 
//	}
//	printf("\n 1 �����  ��������� = %d", s);
//}




//-----------------------------------------------------------------------------------

#include <stdarg.h>

void fun1(char *,...);    // �������� �-��� ������� 1 ���������� ��������
void fun2(char *,...);
void fun3(char *,...);

int main()
{
  setlocale(LC_ALL, "Russian");
  char *s1="aaa aaaa aaaa",
       *s2="bb bbb b",
       *s3="cccc cccccc  ccccc",
       *s4=nullptr;
  fun1(s1,s2,s3,s4);
  fun2(s1,s2,s3,nullptr);
  fun3(s1,s2,s3,s4);
  puts("\n");
}

  // �������� � ������� ����� ��������� ��������� ���������� ������
  // ���������� ���������� �� ������������ � ������� ������ ��������������
  // � �������������� ��������� �� ��������� ����  char     (char **p)
void fun1(char *s,...)
{ char **p;
  p=&s;
  puts("\n\n �������  - fun 1 -");
  while(*p)                 // ���� ���� � ����� �� NULL
  { printf("\n%s",*p);
    p++;                    // ������� � ������ �������� (������) � �����
  }                         // p ������������� �� �������� = ����.���������
}

  // �������� � ������� ����� ��������� ��������� ���������� ������
  // ���������� ���������� �� ������������ � ������� ������ ��������������
  // � �������������� ����������� ��������� �� ���������    (void **p)
void fun2(char *s,...)
{ void **p;
  p=(void **)&s;
  puts("\n\n �������  - fun 2 -");
  while(*(char **)p)    // ���� ���� � ����� �� NULL  (int **)p
  { printf("\n%s",*(char **)p++);
    //p++;	             // ������� � ������ �������� (������) � �����
  }                     // **p ����� �� ��������� � ���� (char **)
}                       // ���������� p ����� �������� ���������


void fun3(char *s,...)
{ va_list p;  
  va_start(p,s);  
  printf("\n%s", s);// p ��������������� �� ������ ����������
  puts("\n\n �������  - fun 3 -"); // ��������   ("bb bbb b"), ������
  do                               // �������� ("aaa aaaa aaaa") �� ���������
  { s=va_arg(p,char *);            // ������� � ������ �������� (������) � �����
    printf("\n%s",s);
  } while(s!=NULL);                // ���� ���� � ����� �� NULL
}



//--------------------------------------------------------------------------------

//enum Type{Char,Int,Float};
//int main()
//{ 
//  void fun(enum Type,...);
//	 fun(Char,'a','b','c','d','e','\0');
//   fun(Int,3,4,7,9,0);
//   fun(Float,1.2,(float)5,5.,(float)0);
//	 return  0;
//}
//
//void fun(enum Type t,...)
//{ char c;
//  void *p=&t;
//  p=((int *)p)+1;
//  puts("\n");
//  switch(t)
//  { case Char : while(*(char *)p)  
//                { printf("%c",*(char *)p);p=((int *)p)+1;} break;
//    case Int  : while(*(int *)p)   
//				{ printf("%3d",*(int *)p);p=((int *)p)+1;} break;
//    case Float: while(*(double *)p)
//				{ printf("%5.2f",*((double *)p));p=((double *)p)+1;}
//   }
//}



//-------------------------------------------------------------------------------

// ���������� ������� � ������������ ������ ���������� ���������� ����
// ������ � ������ (����������) ���������� � �������������� ���������
// ������ ( va_list,  va_start, va_arg,  va_end).

//#include <stdarg.h>
//enum data{Int,Float=2} tp;
//
//void fun(int k, int l, data tp,...)    // k-����� �����
//{ 
//  int si=0;
//  float sf=0;
//  va_list p;           // p - ���������� ���������
//  va_start(p,tp);
//  while(k--)
//  { switch(tp)
//    { case 2: while(l--) // ���� �� ������� ��� ���������� ������
//		   sf+=va_arg(p,double);    // ����� double (float)
//		   break;
//      case Int : while(l--)   // ���� �� ������� ��� ���������� ������
//		   si+=va_arg(p,int);       // ����� int
//    }
//    l=va_arg(p,int);          // ����������� ����� ��������� � ������ (int)
//    tp=va_arg(p,enum data);   // ����������� ������� ���� ��������� ������
//  }
//  va_end(p);
//  printf("\n  si= %d   sf= %lf",si,sf);
//}
//
//int main()
//{ 
//  fun(3,2,Int,1,2,3,Float,1.2,.8,2.5,4,Int,2,3,4,5);
//  printf("\n");
//  return 0;
//}




//---------------------------------------------------------------------------------


//void ** fun(int,...);
//
//int main()
//{ setlocale(LC_ALL,"Russian" );
//  float d1=1.1,d2=2.2,d3=3.3,d4=4.4;
//  int i1=5,i2=6,i3=7,i4=8;
//  void **ms;              // ��� �������� �� fun ������� ���������� ����
//  //puts("������� ����� �����");
//  //scanf("%d%d%d%d",&i1,&i2,&i3,&i4);
//  //puts("������� ������� �����");
//  //scanf("%f%f%f%f",&d1,&d2,&d3,&d4);
//  ms=fun(3,'f',3,d1,d2,d3,'i',4,i1,i2,i3,i4,'f',2,d3,d4);
//  printf(" \n  sum int= %d  sum float= %5.2f",*((int*)*ms),*((double*)*(ms+1)));
//  return 0;
//}
//       // ������� ������������ ����� ���� int � double
//       // ���������� ������������ � main
//void ** fun(int n,...)    // n-����� �����
//{ 
//  int i,si=0,j;
//  void **ii;
//  double sf=0;
//  char c;
//  ii=(void **)calloc(2,sizeof(void *));
//  void *p=&n;        // p ��������������� �� ������ ������
//  p=((int*)p)+1;     // p ������������� �� ������-��� �����
//  while(n--)         // ���� �� ����� ���� ����
//  { c=*(char *)p;    // ���������� �������-����
//    p=((int*)p)+1;   // ��������� �� ����� ���������� � ������
//	i=*(int *)p;     // ���������� ����� ���������� � ������
//	p=((int*)p)+1;   // ����� ��������� �� ������ ���������� � ������
//    switch(c)
//    { case 'f' :   for(j=0;j<i;j++)
//		           {  sf+=*(double *)p;   // ����� double
//		              p=((double*)p)+1; 
//	               }
//	               break;
//      case 'i' :   for(j=0;j<i;j++)
//		           { si+=*(int *)p;      // ����� int
//		             p=((int*)p)+1;
//				   }
//    }
//  }
//  ii[0]=(void*)&si; ii[1]=(void*)&sf;  // ���������� ������� ���������� ����
//  printf(" \n  si= %d  sf= %5.2lf",si,sf);
//  return ii;
//}




//---------------------------------------------------------------------------

//void fun(int,...);
//
//int main()
//{ setlocale(LC_ALL,"Russian" );
//  int *m1, *m2;
//  m1 = (int*)calloc(3,sizeof(int));
//  for (int i = 0; i < 3; i++) m1[i] = i + 1;
//  m2 = (int*)calloc(4, sizeof(int));
//  for (int i = 0; i < 4; i++) m2[i] = i + 5;
//  fun(2,3,m1,4,m2);
//  return 0;
//}
//       
//void fun(int n,...)    // n-����� �����
//{ int k;
//  void **ii;
//  int *jj;
//  jj = (int *)&n;
//  printf("%3d", *(int*)jj);
//  k=*(++jj);
//  
//  while (1)
//  {	  printf("\n");
//	  printf("%3d   ", k);
//	  ii = (void**)(jj+1);
//	  for (int i = 0; i < k; i++)
//		  printf("%3d", *(*(int**)ii + i));
//	  if (!--n) break;
//	  (int**)ii++; (int**)ii++;
//	  jj += 2;
//	  k = *jj;
//  }
//  printf("\n\n");
//}