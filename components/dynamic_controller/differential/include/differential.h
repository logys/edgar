#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#include "wheel.h"
#include "pid.h"
#include "speeds.h"

void differential_setSpeeds(float linear, float angular);
void differential_setKp(float kp);
void differential_setKi(float ki);
void differential_init(Wheel * left, 
		Wheel *right, Pid * left_pid, Pid * right_pid);
void differential_do(void);
void differential_stop(void);
float differential_linearSpeed(void);
float differential_angularSpeed(void);

#endif// DIFFERENTIAL_H
