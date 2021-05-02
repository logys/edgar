//gpio.cpp
#include "gpio.h"
#include <avr/io.h>
#include <stdint.h>

static int8_t const pin_table[32] = {
	PD3, PD4, -1, -1, -1, -1, PB6, PB7,
	PD5, PD6, PD7, PB0, PB1, PB2, PB3, PB4,
	PB5, -1, -1, -1, -1, -1, PC0, PC1,
	PC2, PC3, PC4, PC5, PC6, PD0, PD1, PD2
};

typedef enum {DIRECTION_TYPE, LEVEL_TYPE} REGISTER_TYPE;

static char portOfPin(short const pin);
static volatile uint8_t *registerOfPort(char const port, REGISTER_TYPE);

void gpio_setDirection(short const pin, DIRECTION direction)
{
	char port = portOfPin(pin);
	if(port == '0')
		return;
	volatile uint8_t *register_ = registerOfPort(port, DIRECTION_TYPE);

	if(direction == OUTPUT){
		*register_ |= 1<<pin_table[pin-1];
	}else if(direction == INPUT){
		*register_ &=~(1<<pin_table[pin-1]);
	}
}

static char portOfPin(short const pin)
{
	if(pin >= 30 && pin <= 32 || pin >= 9 && pin <= 11 || pin == 1 || pin == 2){
		return 'd';
	}else if(pin == 8 || pin == 7 || (pin >= 12 && pin <= 17)){
		return 'b';
	}else if(pin >= 23 && pin <= 29){
		return 'c';
	}else
		return '0';
}

static volatile uint8_t * registerOfPort(char const port, REGISTER_TYPE type)
{
	if(type == DIRECTION_TYPE){
		if(port == 'd')
			return &DDRD;
		else if(port == 'b')
			return &DDRB;
		else if(port == 'c')
			return &DDRC;
	}else if(type == LEVEL_TYPE){
		if(port == 'd')
			return &PORTD;
		else if(port == 'b')
			return &PORTB;
		else if(port == 'c')
			return &PORTC;
	}
	return nullptr;
}

void gpio_setLevel(short const pin, LEVEL level)
{
	char port = portOfPin(pin);
	if(port == '0')
		return;
	volatile uint8_t *register_ = registerOfPort(port, LEVEL_TYPE);

	if(level == HIGH){
		*register_ |= 1<<pin_table[pin-1];
	}else if(level == LOW){
		*register_ &=~(1<<pin_table[pin-1]);
	}
}
