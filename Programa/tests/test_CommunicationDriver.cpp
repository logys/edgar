#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "../src/CommunicationDriver.h"

TEST_GROUP(COMMUNICATIONDRIVER)
{
	void setup(void)
	{
	}
	void teardown(void)
	{
	}
};

TEST(COMMUNICATIONDRIVER, assert_test)
{
	CHECK(true);
}
