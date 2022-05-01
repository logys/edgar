#include "differential.h"
#include "wheel.h"
#include "pid.h"
//#include "esp_log.h"

//static const char * tag = "differential";

#define WHEELS_D 20.0

static Wheel * left_wheel;
static Wheel * right_wheel;
static float vl_ref = 0;
static float vr_ref = 0;
static Pid * left_pid_;
static Pid * right_pid_;

static void limitCv(float * cv);

void differential_setSpeeds(float linear, float angular)
{
	vl_ref = linear - WHEELS_D*angular/2.0;
	vr_ref = linear + WHEELS_D*angular/2.0;
	pid_setSp(left_pid_, vl_ref);
	pid_setSp(right_pid_, vr_ref);
}

// kp = 30, ki = 0.1
void differential_setKp(float kp)
{
	pid_setKp(left_pid_, kp);
	pid_setKp(right_pid_, kp);
}

void differential_setKi(float ki)
{
	pid_setKi(left_pid_, ki);
	pid_setKi(right_pid_, ki);
}

static float current_vl;
static float current_vr;
static float cv_vl = 0; //variable de control
static float cv_vr = 0;

void differential_do(void)
{
	//ESP_LOGI(tag, "vl_ref,: %0.2f, c_vl :%0.4f, cv_vl; %0.4f", vl_ref, current_vl, cv_vl);
	//ESP_LOGI(tag, "vr_ref,: %0.2f, c_vr :%0.4f, cv_vr; %0.4f", vr_ref, current_vr, cv_vr);
	current_vl = wheel_tangentialSpeed(left_wheel);
	current_vr = -wheel_tangentialSpeed(right_wheel);
	cv_vl = pid_do(left_pid_, current_vl);
	cv_vr = pid_do(right_pid_, current_vr);
	limitCv(&cv_vl);
	limitCv(&cv_vr);
	wheel_setSpeedPercent(left_wheel, -cv_vl);
	wheel_setSpeedPercent(right_wheel, cv_vr);
}

void differential_init(Wheel * left_wheel_, Wheel * right_wheel_, 
		Pid * left_pid, Pid * right_pid)
{
	left_wheel = left_wheel_;
	right_wheel = right_wheel_;
	vl_ref = 0;
	vr_ref = 0;
	current_vl = 0;
	current_vr = 0;
	cv_vl = 0;
	cv_vr = 0;
	left_pid_ = left_pid;
	right_pid_ = right_pid;

	differential_setKp(30);
	differential_setKi(0.1);
}

void differential_stop(void)
{
	wheel_setSpeedPercent(left_wheel, 0);
	wheel_setSpeedPercent(right_wheel, 0);
}

static void limitCv(float * cv)
{
	if(*cv>100)
		*cv = 100;
	else if(*cv < -100)
		*cv = -100;
}

Speeds differential_speeds(void)
{
	return (Speeds){
		.linear = (vl_ref + vr_ref)/2.0,
		.angular = (-vl_ref + vr_ref)/WHEELS_D
	};
}
