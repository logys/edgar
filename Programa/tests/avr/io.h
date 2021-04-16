#ifndef _AVR_IOM328P_H_
#define _AVR_IOM328P_H_ 

#include<stdint.h>

extern uint8_t DDRB;
extern uint8_t PORTB;
extern uint8_t PINB;
#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7

extern uint8_t DDRD;
extern uint8_t PORTD;
extern uint8_t PIND;
#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

extern uint8_t DDRC;
extern uint8_t PORTC;
#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5
#define PC6 6
#define PC7 7

extern uint8_t TCCR0A;
#define WGM00 0
#define WGM01 1
#define COM0B0 4
#define COM0B1 5
#define COM0A0 6
#define COM0A1 7

extern uint8_t TCCR0B;
#define CS00 0
#define CS01 1
#define CS02 2
#define WGM02 3

extern uint8_t OCR0A;
extern uint8_t OCR0B;
extern uint8_t TCCR1A;
#define WGM10 0
#define WGM11 1
extern uint8_t TCCR1B;
#define WGM12 3
#define WGM13 4
extern uint8_t TCCR2A;
#define WGM20 0
#define WGM21 1
extern uint8_t TCCR2B;
#define WGM22 3

extern uint8_t SREG;
#define I 	7

extern uint8_t TCNT1;
extern uint8_t TCCR1;
#define CS10 0
#define CS11 1
#define CS12 2
#define CS13 3

extern uint8_t OCR1A;

extern uint8_t TIMSK;
#define OCIE1A 6

extern uint8_t GIMSK;
#define PCIE 5
#define INT0 6


extern uint8_t PCMSK;
#define PCINT0 0
#define PCINT3 3
#define PCINT4 4

extern uint8_t CLKPR;
#define CLKPS0 0
#define CLKPS1 1

extern uint8_t PLLCSR;
#define PCKE 2

extern uint8_t MCUCR;
#define ISC00 0
#define ISC01 1


#endif // _AVR_IOM328P_H_
