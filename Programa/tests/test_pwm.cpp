#include "CppUTest/TestHarness.h"
#include <avr/io.h>
#include "../src/pwm.h"
TEST_GROUP(PWM)
{
	void setup(void)
	{
	}
	void teardown(void)
	{
	}
};

TEST(PWM, enablePwmPin)
{
	TCCR0A = 0x00;

	pwm_enablePin(9);

	BITS_EQUAL(1<<COM0B1|1<<COM0B0, TCCR0A, 1<<COM0B1|1<<COM0B0);
}

TEST(PWM, disablePwmPin)
{
	TCCR0A = 0xC0;

	pwm_disablePin(10);

	BITS_EQUAL(0, TCCR0A, 1<<COM0A1|1<<COM0A0);
}

TEST(PWM, enableFast)
{
	TCCR0A = 0x00;

	pwm_enablePin(9);

	BITS_EQUAL(1<<WGM01|1<<WGM00, TCCR0A, 1<<WGM01|1<<WGM00);
}

TEST(PWM, enableCounter)
{
	TCCR0B = 0x00;

	pwm_enableTimer();

	BITS_EQUAL(1<<CS01, TCCR0B, 0x03);
}

TEST(PWM, disableCounter)
{
	TCCR0B = 0x2;

	pwm_disableTimer();

	BITS_EQUAL(0<<CS00, TCCR0B, 0x07);
}

TEST(PWM, setWorkCicle)
{
	OCR0B = 100;
	short wc = 0;
	short pin = 9;

	pwm_setWorkCycle(pin, wc);

	CHECK_EQUAL(255, OCR0B);
}

TEST(PWM, overflowWorkCicle)
{
	OCR0A = 100;
	short wc = 101;
	short pin = 10;

	pwm_setWorkCycle(pin, wc);

	CHECK_EQUAL(0, OCR0A);
}
