#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"li.h"

int main()
{
	Node1 *vec,*head,*k;	
	Node *A,*B,*C,*d,*e,*f,*one;
	int m=3,n=3,r;
	double two,s;
	head=constructVec("cat.dat",m,n);
	r=rank(head,m,n);
	if(r<3)
		printf("Collinear\n");
	else
		printf("Non-Collinear\n");
	A=loadtxt("A.dat");
	B=loadtxt("B.dat");
	C=loadtxt("C.dat");
	d=linalg_sub(B,A);
	e=linalg_sub(C,B);
	f=transpose(e);
	one=matmul(f,d,1,3);
	two=linalg_norm(f,1,3);
	s=one->value/two;
	printf("B divides AC in the ratio %lf\n",s);
	save(s);

	return 0;	
}

