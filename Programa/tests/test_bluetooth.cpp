#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "../src/bluetooth.h"
#include "../src/command_selector.h"
#include "../src/direction.h"

class SelectorMock : public CommandSelector{
	virtual void sendMovement(Direction direction) override
	{
		mock().actualCall("send").withParameter("direction", (int)direction);
	}
};

CommandSelector * selector;
CommunicationDriver * ble;

TEST_GROUP(BLUETOOTH)
{
	void setup(void)
	{
		selector = new SelectorMock();
		ble = new Bluetooth(selector);
	}
	void teardown(void)
	{
		delete selector;
		delete ble;
		mock().clear();
	}
};

TEST(BLUETOOTH, ceroToForward)
{
	mock().expectOneCall("send").withParameter("direction",(int) Direction::FORWARD);

	ble->sendUserInput(0);

	mock().checkExpectations();
}

TEST(BLUETOOTH, oneToBackward)
{
	mock().expectOneCall("send").withParameter("direction",(int) Direction::BACKWARD);

	ble->sendUserInput(1);

	mock().checkExpectations();
}
