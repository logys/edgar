#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "../src/motorDc.h"
#include "../src/motor.h"
#include "../src/gpio.h"

static Motor * motor;

TEST_GROUP(MOTOR)
{
	void setup(void)
	{
	}
	void teardown(void)
	{
		mock().clear();
	}
};

void gpio_setDirection(short const pin, DIRECTION direction) 
{
	mock().actualCall("gpio_setDirection");
}

void gpio_setLevel(short const pin, LEVEL level) 
{
	if(level == HIGH)
		mock().actualCall("gpio_setLevelHigh");
	else
		mock().actualCall("gpio_setLevelLow");
}

TEST(MOTOR, enablePin)
{
	mock().expectOneCall("gpio_setDirection");
	short const pin = 1;

	MotorDc dummy(pin);

	mock().checkExpectations();
}

TEST(MOTOR, on)
{
	mock().expectOneCall("gpio_setLevelHigh");
	mock().ignoreOtherCalls();
	short const pin = 1;
	MotorDc dummy(pin);

	dummy.on();

	mock().checkExpectations();
}

TEST(MOTOR, off)
{
	mock().expectOneCall("gpio_setLevelLow");
	mock().ignoreOtherCalls();
	short const pin = 1;
	MotorDc dummy(pin);

	dummy.off();

	mock().checkExpectations();
}
