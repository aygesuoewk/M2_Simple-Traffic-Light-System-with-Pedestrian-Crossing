/**
 * @file traffic.c
 * @author Stephen J
 * @brief 
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define F_CPU 16000000L

#include <avr/io.h>          
#include <util/delay.h>




#define  Red 5		
#define  Yellow 2000	
#define  Green 4			
#define  Blink 500		


void delaySec(int sec)
{
	while(sec>0)
	{
	 sec--;
	 _delay_ms(1000);
	}
}

void Red_Signal(void)
{	
	PORTB=PINB & 0B11110000;
	PORTB=PINB | 0B00001000;
}

void Yellow_Signal(void)
{
	PORTB=PINB & 0B11110000;
	PORTB=PINB | 0B00000100;
}

void Green_Signal(void)
{
	PORTB=PINB & 0B11110000;
	PORTB=PINB | 0B00000010;
}

void Walk(void)
{
	PORTB=PINB & 0B11001110;
	PORTB=PINB | 0B00010000;
}

void Dont_walk(void)
{
	PORTB=PINB & 0B11001110;
	PORTB=PINB | 0B00100000;
}

void walk_b(void)
{
	PORTB=PINB & 0B11001110;
	PORTB=PINB | 0B00000000;
}

void walk_a(int z)
{
	while(z>0)
		{
			z--;		
			 Walk();
			_delay_ms(Blink);
			 walk_b();
			_delay_ms(Blink);
		}
	walk_b();
	_delay_ms(Blink);
}


int main (void)
{
	PORTC=0X00;
	PORTB=0x00;
	PORTD=0x00;
	
	DDRB=0xff; 	
	
	while(1)
	{
		Yellow_Signal();
		_delay_ms(Yellow);
		Red_Signal();
		_delay_ms(Yellow);
		Walk();
		delaySec(Red);		
		walk_a(6);
		Dont_walk();
		Green_Signal();
		delaySec(Green);	
	}

 return(0);

}