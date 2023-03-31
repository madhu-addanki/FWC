#include<Arduino.h>
int x,y,z,A=0,B,C,D,Y1,Y2;
void disp(int D,int C,int B,int A)
{
	digitalWrite(2,A);
}
void setup()
{
	pinMode(2,OUTPUT);
	pinMode(5,INPUT);
	pinMode(6,INPUT);
	pinMode(7,INPUT);
}
void loop()
{
	x=digitalRead(5);
	y=digitalRead(6);
	z=digitalRead(7);
	Y1=(x||y)^z;
	Y2=x^(y||z);
	A=0;
	if(Y1==Y2)
	{
		A=1;
	}
	disp(D,C,B,A);
}

