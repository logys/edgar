#include "motorDc.h"
#include <avr/io.h>

MotorDc::MotorDc(short const pin)
{
	DDRD |= 1<<PD3;
}
void MotorDc::on(void)
{
	PORTD |= 1<<PD3;
}
void MotorDc::off(void)
{
	PORTD &= ~(1<<PD3);
}
