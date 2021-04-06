#include "push.h"
#include <avr/io.h>

Push::Push(short const pin)
{
	DDRD &= ~(1<<PD2);
	PORTD |= 1<<PD2;
}

bool Push::pushed(void)
{
	if((PIND&(1<<PD2)) == 0)
		return true;
	else
		return false;
}
