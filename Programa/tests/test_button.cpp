#include "CppUTest/TestHarness.h"
#include <avr/io.h>
#include "../src/button.h"
#include "../src/push.h"

Button * push_button;

TEST_GROUP(BUTTON)
{
	void setup(void)
	{
		short const pin = 1;
		push_button = new Push(pin);
	}
	void teardown(void)
	{
		delete push_button;
	}
};

TEST(BUTTON, unpushed)
{
	PIND = 0x00;

	bool pushed = push_button->pushed();

	CHECK_FALSE(pushed);
}

TEST(BUTTON, pushed)
{
	PIND = 0xFF;

	bool pushed = push_button->pushed();

	CHECK(pushed);
}

TEST(BUTTON, pushed_PD2)
{
	PIND =(1<<PD2);

	bool pushed = push_button->pushed();

	CHECK(pushed);
}

TEST(BUTTON, as_input)
{
	DDRD = 0xFF;

	Push dummy(1);

	BITS_EQUAL(0<<PD2, DDRD, 1<<PD2);
}
