#include "differential.h"
#include "wheel.h"
#include "esp_log.h"

static const char * tag = "differential";

#define WHEELS_D 0.20

static Wheel * left_wheel;
static Wheel * right_wheel;
static float vl_ref = 0;
static float vr_ref = 0;

static void limitCv(float * cv);

static float l_linear = 0;
static float l_angular = 0;

void differential_setSpeeds(float linear, float angular)
{
	l_linear = linear;
	l_angular = angular;
	vl_ref = l_linear - WHEELS_D*l_angular/2.0;
	vr_ref = l_linear + WHEELS_D*l_angular/2.0;
}

void differential_setLinearSpeed(float speed)
{
	differential_setSpeeds(speed, l_angular);
}

void differential_setAngularSpeed(float speed)
{
	differential_setSpeeds(l_linear, speed);
}

#define KP 20
static float current_vl;
static float current_vr;
static float cv_vl = 0; //variable de control
static float cv_vr = 0;
static float error_vl = 0;
static float error_vr = 0;

void differential_do(void)
{
	ESP_LOGI(tag, "vl_ref,: %0.2f, c_vl :%0.4f, cv_vl; %0.4f",vl_ref, current_vl, cv_vl);
	ESP_LOGI(tag, "vr_ref,: %0.2f, c_vr :%0.4f, cv_vr; %0.4f",vr_ref, current_vr, cv_vr);
	current_vl = wheel_tangentialSpeed(left_wheel);
	current_vr = -wheel_tangentialSpeed(right_wheel);
	error_vl = vl_ref - current_vl;
	error_vr = vr_ref - current_vr;
	cv_vl += KP*error_vl;
	cv_vr += KP*error_vr;
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
	error_vl = 0;
	error_vr = 0;
	l_linear = 0;
	l_angular = 0;
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
