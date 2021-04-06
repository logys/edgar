#include "CppUTest/TestHarness.h"
#include <avr/io.h>
#include "../src/motorDc.h"
#include "../src/motor.h"

static Motor * motor;

TEST_GROUP(MOTOR)
{
	void setup(void)
	{
		short const pin = 1;
		motor = new MotorDc(pin);
	}
	void teardown(void)
	{
		delete motor;
	}
};

TEST(MOTOR, On)
{
	PORTD = 0x00;

	motor->on();

	BITS_EQUAL(1<<PD3, PORTD, 1<<PD3);
}

TEST(MOTOR, off)
{
	PORTD = 0xFF;

	motor->off();

	BITS_EQUAL(0<<PD3, PORTD, 1<<PD3);
}

TEST(MOTOR, only_on_PD3_affected)
{
	PORTD = 0x00;

	motor->on();

	BITS_EQUAL(0<<PD0, PORTD, ~(1<<PD3));
}

TEST(MOTOR, only_off_PD3_affected)
{
	PORTD = 0xFF;

	motor->off();

	BITS_EQUAL(0xFF, PORTD, ~(1<<PD3));
}


TEST(MOTOR, as_output)
{
	DDRD = 0x00;

	MotorDc dummy(1);

	BITS_EQUAL(1<<PD3, DDRD, 1<<PD3);
}
