#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "../src/differential.h"
#include "../src/motor.h"

class Motor_stub : public Motor{
	virtual void on(void) override
	{
		mock().actualCall("on");
	}
	virtual void off(void) override
	{
		mock().actualCall("off");
	}
};

static Differential * differential;
Motor *left;
Motor *right;

TEST_GROUP(DIFFERENTIAL)
{
	void setup(void)
	{
		left = new Motor_stub();
		right = new Motor_stub();
		differential = new Differential(left, right);
	}
	void teardown(void)
	{
		delete left;
		delete right;
		delete differential;
		mock().clear();
	}
};

TEST(DIFFERENTIAL, On)
{
	mock().expectNCalls(2, "on");

	differential->on();

	mock().checkExpectations();
}

TEST(DIFFERENTIAL, off)
{
	mock().expectNCalls(2, "off");

	differential->off();

	mock().checkExpectations();
}
