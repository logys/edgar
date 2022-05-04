#include "unity.h"
#include "controller.h"
#include <stdbool.h>
#include "point.h"
#include <math.h>
#include "speeds.h"


void setUp(void)
{
}

void test_should_set_point(void)
{
	Point want = {.x = 0, .y = 20};

	controller_setPoint(want);

	Point get = controller_getReferencePoint();
	TEST_ASSERT_EQUAL(want.x, get.x);
	TEST_ASSERT_EQUAL(want.y, get.y);
}

void test_should_calculate_errors(void)
{
	Point point = {.x = 10, .y = 0};
	controller_setPoint(point);

	controller_do();
	PositionErrors get = controller_getErrors();

	TEST_ASSERT_EQUAL(10, get.dx);
	TEST_ASSERT_EQUAL(0, get.dy);
	TEST_ASSERT_EQUAL_FLOAT(0, get.dphi);
}

void test_should_calculate_speeds(void)
{
	Point point = {.x = 0, .y = 10};
	controller_setPoint(point);

	Speeds get = controller_do();

	TEST_ASSERT_EQUAL(10, get.linear);
	TEST_ASSERT_EQUAL(3.141586/2, get.angular);
}

void test_should_calculate_positions(void)
{
	Point point = {.x = 10, .y = 10};
	controller_setPoint(point);
	float dt = 0.1;
	Speeds speeds = {.linear = 1, .angular = 0};

	controller_do();
	Position get = controller_updatePosition(speeds);

	TEST_ASSERT_EQUAL_FLOAT(1*dt, get.x);
	TEST_ASSERT_EQUAL_FLOAT(0*dt, get.y);
	TEST_ASSERT_EQUAL_FLOAT(0.05*dt, get.phi);
}

void test_should_go_to_point(void)
{
	Point point = {.x = 10, .y = 10};
	controller_setPoint(point);

	Speeds speeds = {};
	for(int i = 0; i<10; i++){
		speeds = controller_do();
		controller_updatePosition(speeds);
	}
	Position get = controller_updatePosition(speeds);

	TEST_ASSERT_EQUAL_FLOAT(10, get.x);
	TEST_ASSERT_EQUAL_FLOAT(10, get.y);
}
