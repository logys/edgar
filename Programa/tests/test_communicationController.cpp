#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "../src/communication_controller.h"
#include "../src/robot.h"
#include "../src/communication_driver.h"

class robot_stub : public Robot{
	virtual void forward(void) override
	{
		mock().actualCall("forward");
	}
};

class bluetooth_stub : public CommunicationDriver{
	virtual int getInstruction(void) override
	{
		mock().actualCall("getInstruction");
		return mock().intReturnValue();
	}
};

TEST_GROUP(CommunicationController)
{
	CommunicationController * controller;
	void setup(void)
	{
		controller = new CommunicationController();
	}

	void teardown(void)
	{
		delete controller;
		mock().clear();
	}
};
/*
TEST(CommunicationController, forwardToRobot)
{
	mock().expectOneCall("getInstruction").andReturnValue(1);
	mock().expectOneCall("fordward");

	controller->sendCommand();

	mock().checkExpectations();
}
*/
