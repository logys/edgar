#include "serial.h"
#include <avr/io.h>

static CommunicationDriver * ble;

void serial_init(CommunicationDriver * driver)
{
	ble = driver;
	//Habilita transmisión y recepción
	UCSR0B |= 1 << TXEN0 | 1 << RXEN0;
	//Baudrate a 9600bps, ref datasheet
	UBRR0L = 103;
	//Tamaño de datos 8 bits
	UCSR0C |= 1 << UCSZ00 | 1 << UCSZ01;
	//modo asíncrono 
	UCSR0C &= ~(1<<UMSEL00 | 1<<UMSEL01);
}

short serial_read(void)
{
	return UDR0;
}

bool serial_dataNew(void)
{
	return UCSR0A & 1<<RXC0;
}

void serial_asyncCall(short data)
{
	ble->sendUserInput(data);
}
