#include "differential.h"
#include "wheel.h"
#include "pid.h"
#include "esp_log.h"

static const char * tag = "differential";

#define WHEELS_D 200

static Wheel * left_wheel;
static Wheel * right_wheel;
static float vl_ref = 0;
static float vr_ref = 0;
static float _linear = 0;
static float _angular = 0;
static Pid _left_pid;
static Pid _right_pid;

static void limitCv(float * cv);

void differential_setSpeeds(float linear, float angular)
{
	_linear = linear;
	_angular = angular;
	vl_ref =10*(_linear - WHEELS_D*_angular/2.0);
	vr_ref =10*(_linear + WHEELS_D*_angular/2.0);
	pid_setSp(&_left_pid, vl_ref);
	pid_setSp(&_right_pid, vr_ref);
}

void differential_setLinearSpeed(float speed)
{
	differential_setSpeeds(speed, _angular);
}

void differential_setAngularSpeed(float speed)
{
	differential_setSpeeds(_linear, speed);
}

void differential_setKp(float kp)
{
	pid_setKp(&_left_pid, kp);
	pid_setKp(&_right_pid, kp);
}

void differential_setKi(float ki)
{
	pid_setKi(&_left_pid, ki);
	pid_setKi(&_right_pid, ki);
}

static float current_vl;
static float current_vr;
static float cv_vl = 0; //variable de control
static float cv_vr = 0;

void differential_do(void)
{
	ESP_LOGI(tag, "vl_ref,: %0.2f, c_vl :%0.4f, cv_vl; %0.4f", vl_ref, current_vl, cv_vl);
	ESP_LOGI(tag, "vr_ref,: %0.2f, c_vr :%0.4f, cv_vr; %0.4f", vr_ref, current_vr, cv_vr);
	current_vl = wheel_tangentialSpeed(left_wheel);
	current_vr = -wheel_tangentialSpeed(right_wheel);
	cv_vl = pid_do(&_left_pid, current_vl);
	cv_vr = pid_do(&_right_pid, current_vr);
	limitCv(&cv_vl);
	limitCv(&cv_vr);
	wheel_setSpeedPercent(left_wheel, -cv_vl);
	wheel_setSpeedPercent(right_wheel, cv_vr);
}

void differential_init(Wheel * left_wheel_, Wheel * right_wheel_)
{
	left_wheel = left_wheel_;
	right_wheel = right_wheel_;
	vl_ref = 0;
	vr_ref = 0;
	current_vl = 0;
	current_vr = 0;
	cv_vl = 0;
	cv_vr = 0;
	_linear = 0;
	_angular = 0;
	_left_pid = pid_create();
	_right_pid = pid_create();
}

void differential_stop(void)
{
	differential_setSpeeds(0, 0);
}

float differential_linearSpeed(void)
{
	return current_vl/2.0 + current_vr/2.0;
}

float differential_angularSpeed(void)
{
	return (current_vr-current_vl)/WHEELS_D;
}

static void limitCv(float * cv)
{
	if(*cv>100)
		*cv = 100;
	else if(*cv < -100)
		*cv = -100;
}
