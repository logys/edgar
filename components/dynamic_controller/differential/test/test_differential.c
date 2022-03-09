#include "unity.h"
#include "fff.h"
#include "differential.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(float, wheel_tangentialSpeed, Wheel *);
FAKE_VOID_FUNC(wheel_setSpeedPercent, Wheel *, float);

Wheel left;
Wheel right;
void setUp()
{
	differential_init(&left, &right);
	RESET_FAKE(wheel_tangentialSpeed);
	RESET_FAKE(wheel_setSpeedPercent);
	FFF_RESET_HISTORY();
}

void test_linearSpeed(void)
{
	float wheelsSpeeds[] = {1, -1};
    	SET_RETURN_SEQ(wheel_tangentialSpeed, wheelsSpeeds, 2);
	differential_do();

	float get = differential_linearSpeed();
	float want = 1;
	TEST_ASSERT_EQUAL(want, get);
}

void test_angularSpeed(void)
{
	float wheelsSpeeds[] = {-1, -1};
    	SET_RETURN_SEQ(wheel_tangentialSpeed, wheelsSpeeds, 2);
	differential_do();

	float get = differential_angularSpeed();
	float want = 10;
	TEST_ASSERT_EQUAL_FLOAT(want, get);
}

void test_setLinearSpeed(void)
{
	differential_setLinearSpeed(1);
	float wheelsSpeeds[] = {1, -1};
    	SET_RETURN_SEQ(wheel_tangentialSpeed, wheelsSpeeds, 2);
	differential_do();

	float get = wheel_setSpeedPercent_fake.arg1_val;
	float want = 0;
	TEST_ASSERT_EQUAL_FLOAT(want, get);
}

void test_setAngularSpeed(void)
{
	differential_setAngularSpeed(10);
	float wheelsSpeeds[] = {-1, -1};
    	SET_RETURN_SEQ(wheel_tangentialSpeed, wheelsSpeeds, 2);
	differential_do();

	float get = wheel_setSpeedPercent_fake.arg1_val;
	float want = 0;
	TEST_ASSERT_EQUAL_FLOAT(want, get);
}

void test_controll(void)
{
	differential_setLinearSpeed(1);
	float wheelsSpeeds[] = {-0, -0};
    	SET_RETURN_SEQ(wheel_tangentialSpeed, wheelsSpeeds, 2);
	differential_do();

	float get = wheel_setSpeedPercent_fake.arg1_val;
	float want = 20;
	TEST_ASSERT_EQUAL_FLOAT(want, get);
}
