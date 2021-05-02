#include "CppUTest/TestHarness.h"
#include "../src/motorDc.h"
#include "../src/motor.h"
#include "../src/gpio.h"
#include "../src/pwm.h"
#include <avr/io.h>

static Motor * motor;

TEST_GROUP(MOTOR)
{
	void setup(void)
	{
		short const pin_enable = 9;
		short const pin_input1 = 1;
		short const pin_input2 = 2;
		motor = new MotorDc(9, 1, 2);
	}
	void teardown(void)
	{
		delete motor;
	}
};

TEST(MOTOR, enable_pwm_timer)
{
	TCCR0B = 0x00;

	MotorDc dummy(9, 1, 2);

	BITS_EQUAL(1<<CS01, TCCR0B, 1<<CS01);
}

TEST(MOTOR, enable_pin_pwm)
{
	TCCR0A = 0x00;

	motor->forward(0);

	BITS_EQUAL(1<<COM0B1|1<<COM0B0, TCCR0A, 1<<COM0B1|1<<COM0B0);
}

TEST(MOTOR, forward)
{
	OCR0B = 0x00;

	motor->forward(100);

	CHECK_EQUAL(255, OCR0B);
}

TEST(MOTOR, backward)
{
	OCR0B = 0x00;

	motor->backward(100);

	CHECK_EQUAL(255, OCR0B);
}

TEST(MOTOR, off)
{
	TCCR0A = 0xFF;

	motor->off();

	BITS_EQUAL(0, TCCR0A, 1<<COM0B1|1<<COM0B0);
}
