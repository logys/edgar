#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "../src/differential.h"
#include "../src/motor.h"

class Motor_stub : public Motor{
	virtual void forward(short const power) override
	{
		mock().actualCall("forward");
	}
	virtual void backward(short const power) override
	{
		mock().actualCall("backward");
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

TEST(DIFFERENTIAL, forward)
{
	mock().expectOneCall("forward");
	mock().expectOneCall("backward");

	differential->forward();

	mock().checkExpectations();
}

TEST(DIFFERENTIAL, backward)
{
	mock().expectOneCall("backward");
	mock().expectOneCall("forward");

	differential->backward();

	mock().checkExpectations();
}

TEST(DIFFERENTIAL, off)
{
	mock().expectNCalls(2, "off");

	differential->off();

	mock().checkExpectations();
}
