#include<avr/io.h>
#include<util/delay.h>
#include<stdbool.h>

int main(void)
{
	int a,b,c;
	int y;
	PORTB=0b00000111;
	DDRD=0b000000100;
	while(1)
	{
		a=(PINB & (1<<PIND0))==(1<<PIND0);
		b=(PINB & (1<<PIND1))==(1<<PIND1);
		c=(PINB & (1<<PIND2))==(1<<PIND2);
		y=(a+(!b)&&c);
		PORTD=(y<<PB2);
	}
	return 0;
}

