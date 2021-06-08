#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "../src/robotController.h"
#include "../src/robot.h"

class RobotMock : public Robot{
	virtual void moveForward(void) override
	{
		mock().actualCall("forward");
	}
	virtual void moveBackward(void) override
	{
		mock().actualCall("backward");
	}
};

static CommandSelector * controller;
static Robot * robot;

TEST_GROUP(ROBOTCONTROLLER)
{
	void setup(void)
	{
		robot = new RobotMock();
		controller = new RobotController(robot);
	}
	void teardown(void)
	{
		delete robot;
		delete controller;
		mock().clear();
	}
};

TEST(ROBOTCONTROLLER, forwardCallRobotForward)
{
	mock().expectOneCall("forward");

	controller->sendMovement(Direction::FORWARD);

	mock().checkExpectations();
}

TEST(ROBOTCONTROLLER, backwardCallRobot)
{
	mock().expectOneCall("backward");

	controller->sendMovement(Direction::BACKWARD);

	mock().checkExpectations();
}
