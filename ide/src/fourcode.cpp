#include<Arduino.h>
int x,y,A,B,C,D;
void disp(int D,int C,int B,int A)
{
	digitalWrite(2,A);
}
void setup()
{
	pinMode(2,OUTPUT);
	pinMode(5,INPUT);
	pinMode(6,INPUT);
}
void loop()
{
	x=digitalRead(5);
	y=digitalRead(6);
	A=x^y;
	disp(D,C,B,A);
}
