#include "CppUTest/TestHarness.h"
#include <avr/io.h>
#include "../src/timer_delay.h"
#include "../src/timer.h"

static Timer * timer;

TEST_GROUP(TIMER)
{
	void setup(void)
	{
		short const pin = 1;
		timer = new Timer_delay();
	}
	void teardown(void)
	{
		delete timer;
	}
};

/*
TEST(TIMER, )
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

	Single_motor dummy(1);

	BITS_EQUAL(1<<PD3, DDRD, 1<<PD3);
}
*/
