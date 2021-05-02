#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "../src/robot.h"
#include "../src/power_train.h"
#include "../src/timer.h"

class Train_stub : public PowerTrain{
	virtual void forward(void) override
	{
		mock().actualCall("forward");
	}
	virtual void backward(void) override
	{
		mock().actualCall("backward");
	}
	virtual void off(void) override
	{
		mock().actualCall("off");
	}
};

class TimerStub : public Timer{
	virtual void enable(void) override
	{
		mock().actualCall("enable");
	}
	virtual unsigned long getTime(void) override
	{
		return mock().actualCall("getTime").returnIntValue();
	}
};

PowerTrain * train;
Timer * timer;
Robot * robot;

TEST_GROUP(ROBOT)
{

	void setup(void)
	{
		train = new Train_stub();
		timer = new TimerStub();
		robot = new Robot(train, timer);
	}

	void teardown(void)
	{
		delete train;
		delete timer;
		delete robot;
		mock().clear();
	}
};

TEST(ROBOT, forward)
{
	mock().expectOneCall("forward");
	mock().expectOneCall("enable");
	mock().expectOneCall("getTime").andReturnValue(1000);
	mock().expectOneCall("off");

	robot->moveForward();

	mock().checkExpectations();
}

TEST(ROBOT, backward)
{
	mock().expectOneCall("backward");
	mock().expectOneCall("enable");
	mock().expectOneCall("getTime").andReturnValue(1000);
	mock().expectOneCall("off");

	robot->moveBackward();

	mock().checkExpectations();
}
