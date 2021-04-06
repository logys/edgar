#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "../src/robot.h"
#include "../src/motor.h"
#include "../src/timer.h"

class MotorStub : public Motor{
	virtual void on(void) override
	{
		mock().actualCall("on");
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
class ButtonStub : public Button{
	virtual bool pushed(void) override
	{
		return mock().actualCall("pushed").returnBoolValue();
	}
};

Button * button;
Motor * motor;
Timer * timer;
Robot * robot;

TEST_GROUP(ROBOT)
{

	void setup(void)
	{
		button = new ButtonStub();
		motor = new MotorStub();
		timer = new TimerStub();
		robot = new Robot(motor, timer, button);
	}

	void teardown(void)
	{
		delete button;
		delete motor;
		delete timer;
		delete robot;
		mock().clear();
	}
};

TEST(ROBOT, MotorPowerOn)
{
	mock().expectOneCall("pushed").andReturnValue(true);
	mock().expectOneCall("on");
	mock().ignoreOtherCalls();

	robot->moveFordward();

	mock().checkExpectations();
}

TEST(ROBOT, TimerOn)
{
	mock().expectOneCall("pushed").andReturnValue(true);
	mock().expectOneCall("enable");
	mock().ignoreOtherCalls();

	robot->moveFordward();

	mock().checkExpectations();
}

TEST(ROBOT, UnpoushedNoInit)
{
	mock().expectOneCall("pushed").andReturnValue(false);
	mock().expectNoCall("on");

	robot->moveFordward();

	mock().checkExpectations();
}


TEST(ROBOT, getCeroTimeAtInit)
{
	mock().expectOneCall("pushed").andReturnValue(true);
	mock().expectOneCall("getTime").andReturnValue(0);
	mock().ignoreOtherCalls();

	robot->moveFordward();

	mock().checkExpectations();
}

TEST(ROBOT, lessOfOneMinuteMotorOn)
{
	mock().expectOneCall("pushed").andReturnValue(true);
	mock().expectOneCall("getTime").andReturnValue(999);
	mock().expectNoCall("off");
	mock().ignoreOtherCalls();

	robot->moveFordward();

	mock().checkExpectations();
}
TEST(ROBOT, poweroffMotorAfterOneSecond)
{
	mock().expectOneCall("pushed").andReturnValue(true);
	mock().expectOneCall("getTime").andReturnValue(1000);
	mock().expectOneCall("off");
	mock().ignoreOtherCalls();

	robot->moveFordward();

	mock().checkExpectations();
}
