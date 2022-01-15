#ifndef MOTOR_H
#define MOTOR_H

#include "pwm.h"
#include "encoder.h"

typedef struct Motor{
	Pwm * pwmIn1;
	Pwm * pwmIn2;
}Motor;

Motor motor_create(Pwm * pwmIn1, Pwm * pwmIn2);
void motor_setWC(Motor * motor, float wc);
void motor_stop(Motor * motor);

#endif// MOTOR_H
