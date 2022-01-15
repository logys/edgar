#include "unity.h"
#include "fff.h"
#include "wheel.h"
#include "encoder.h"
#include <stdint.h>
#include "motor.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(float, encoder_speed, Encoder *);
FAKE_VOID_FUNC(motor_setWC, Motor *, float);

Encoder encoder;
Motor motor;
Wheel wheel;
void setUp(void)
{
	float rad = 2;
	wheel = wheel_create(&motor, &encoder, rad);
	RESET_FAKE(encoder_speed);
	RESET_FAKE(motor_setWC);
}

void test_angularSpeed(void)
{
	encoder_speed_fake.return_val = 5;

	float get = wheel_angularSpeed(&wheel);
	float want = 5;
	TEST_ASSERT_EQUAL(want, get);
}

void test_linearSpeed(void)
{
	encoder_speed_fake.return_val = -1;

	float get = wheel_tangentialSpeed(&wheel);
	float want = -2;
	TEST_ASSERT_EQUAL(want, get);
}

void test_setSpeed(void)
{
	wheel_setSpeedPercent(&wheel, 50);
	float get = motor_setWC_fake.arg1_val;
	float want = 50;
	TEST_ASSERT_EQUAL(want, get);
}
