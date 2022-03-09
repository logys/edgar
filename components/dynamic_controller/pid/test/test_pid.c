#include "unity.h"
//#include "fff.h"
#include "pid.h"

//DEFINE_FFF_GLOBALS;

Pid pid_struct;
Pid * pid = &pid_struct;
void setUp(void)
{
	pid_struct = pid_create();
}

void test_pid_zero_kp_equal_zero(void)
{
	pid_setKp(pid, 0);
	float pv = 100;
	float get = pid_do(pid, 0);
	float want = 0;
	TEST_ASSERT_EQUAL_FLOAT(want, get);
}

void test_zero_setPoint_zero(void)
{
	pid_setSp(pid, 0);
	float get = pid_do(pid, 0);
	float want = 0;
	TEST_ASSERT_EQUAL_FLOAT(want, get);
}

void test_error_difference(void)
{
	pid_setKp(pid, 1);
	pid_setSp(pid, 100);
	float get = pid_do(pid, 0);
	float want = 100;
	TEST_ASSERT_EQUAL_FLOAT(want, get);
}

void test_error_kp_two(void)
{
	pid_setKp(pid, 2);
	pid_setSp(pid, 100);
	float get = pid_do(pid, 0);
	float want = 200;
	TEST_ASSERT_EQUAL_FLOAT(want, get);
}

void test_error_zero_sp_equal_pv(void)
{
	pid_setKp(pid, 2);
	pid_setSp(pid, 100);
	float get = pid_do(pid, 100);
	float want = 0;
	TEST_ASSERT_EQUAL_FLOAT(want, get);
}

void test_for_kp_error_inside_delta(void)
{
	pid_setKp(pid, 0.009);
	pid_setSp(pid, 0.1);
	pid_setKi(pid, 0.0005);
	float pv = 0;
	float wc = 0;
	float period = 0.01;
	for(float time = 0; time<0.1; time += period){
		wc = pid_do(pid, pv);
		pv += wc/period;
		printf("%0.6f\n", pv);
	}
	float get = wc;
	float want = 0;
	TEST_ASSERT_FLOAT_WITHIN(0.001, want, get);
}
