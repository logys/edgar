#include "pwm.h"
#include <avr/io.h>

void pwm_enablePin(short const pin)
{
	//set on compare
	if(pin == 10)
		TCCR0A |= 1<<COM0A1|1<<COM0A0;
	else if(pin == 9)
		TCCR0A |= 1<<COM0B1|1<<COM0B0;
	//enable Fast mode
	TCCR0A |= 1<<WGM01|1<<WGM00;
}

void pwm_disablePin(short const pin)
{
	if(pin == 9)
		TCCR0A &= ~(1<<COM0B1|1<<COM0B0);
	else if(pin == 10)
		TCCR0A &= ~(1<<COM0A1|1<<COM0A0);
}

void pwm_enableTimer(void)
{
	TCCR0B |= 1<<CS01;
}

void pwm_disableTimer(void)
{
	TCCR0B &= ~(1<<CS01);
}

void pwm_setWorkCycle(short const pin, short wc)
{
	if(wc > 100)
		wc = 100;
	if(wc < 0)
		wc = 0;
	short workcycle_in_8bits = -wc/100.0*255 + 255;
	if(pin == 10)
		OCR0A = workcycle_in_8bits;
	else if(pin == 9)
		OCR0B = workcycle_in_8bits;
}
