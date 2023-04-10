.include "/sdcard/Download/FWC/Assignment3/m328Pdef.inc"

	ldi r16,0b00011100 ;pins 2,3,4 for op
	out DDRD,r16
	ldi r17,0b00011111
	out DDRD,r17
	ldi r17,0b11111111
	out PORTD,r17

loop:
	in r17,PIND

	mov r18,r17
	ldi r24,0b10000000
	add r18,r24
	lsr r18
	lsr r18
	lsr r18
	lsr r18
	lsr r18
	.DEF T1=r18

	;Taking Q1 and defining T2
	mov r19,r17
	ldi r24,0b00100000
	add r19,r24
	lsr r19
	lsr r19
	com r19
	.DEF T2=r19

	;Taking Q2 and defining T3
	mov r20,r17
	ldi r24,0b01000000
	add r20,r24
	lsr r20
	lsr r20
	com r20
	.DEF T3=r20

	out PORTD,T1
	out PORTD,T2
	out PORTD,T3


Start:
	rjmp Start
