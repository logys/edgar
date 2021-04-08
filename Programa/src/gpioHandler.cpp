#include "gpioHandler.h"
#include <avr/io.h>

short const pinToGpio(short const pin)
{
	if(pin == 32)
		return PD2;
	else if(pin == 2)
		return PD4;
	return PD3;
}

void gpio_setDirection(short const pin, DIRECTION direction)
{
	short pin_gpio = pinToGpio(pin);
	if(direction == INPUT)
		DDRD &= ~(1<<pin_gpio);
	else
		DDRD |= (1<<pin_gpio);
}

void gpio_setLevel(short const pin, LEVEL level)
{
	short pin_gpio = pinToGpio(pin);
	if(level == LOW)
		PORTD &= ~(1<<pin_gpio);
	else
		PORTD |= (1<<pin_gpio);
}
