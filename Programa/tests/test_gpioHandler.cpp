#include "CppUTest/TestHarness.h"
#include <avr/io.h>
#include "../src/gpio.h"

TEST_GROUP(GPIO)
{
	void setup(void)
	{
	}
	void teardown(void)
	{
	}
};
/*
TEST(GPIO, convertPin1)
{
	short pin = 1;

	short pin_gpio = pinToGpio(pin);

	CHECK_EQUAL(PD3, pin_gpio);
}

TEST(GPIO, convertPin32)
{
	short pin = 32;

	short pin_gpio = pinToGpio(pin);

	CHECK_EQUAL(PD2, pin_gpio);
}

TEST(GPIO, convertPin2)
{
	short pin = 2;

	short pin_gpio = pinToGpio(pin);

	CHECK_EQUAL(PD4, pin_gpio);
}
*/
/*
TEST(GPIO, setDirectionInput)
{
	DDRD = 0xFF;
	short pin = 1;

	gpio_setDirection(pin, INPUT);

	BITS_EQUAL(0<<PD3, DDRD, 1<<PD3);
}

TEST(GPIO, setDirectionOutput)
{
	DDRD = 0x00;
	short pin = 2;

	gpio_setDirection(pin, OUTPUT);

	BITS_EQUAL(1<<PD4, DDRD, 1<<PD4);
}
*/
/*
TEST(GPIO, setLevelLow)
{
	PORTD = 0xFF;
	short pin = 32;
	short pin_gpio = pinToGpio(pin);

	gpio_setLevel(pin, LOW);

	BITS_EQUAL(0<<pin_gpio, PORTD, 1<<pin_gpio);
}

TEST(GPIO, setLevelHigh)
{
	PORTD = 0x00;
	short pin = 32;
	short pin_gpio = pinToGpio(pin);

	gpio_setLevel(pin, HIGH);

	BITS_EQUAL(1<<pin_gpio, PORTD, 1<<pin_gpio);
}
*/
