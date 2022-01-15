#ifndef WHEEL_H
#define WHEEL_H

#include "encoder.h"
#include "motor.h"

typedef struct Wheel{
	Encoder * encoder;
	Motor * motor;
	float rad;
}Wheel;

Wheel wheel_create(Motor * motor, Encoder * encoder, float rad);
float wheel_angularSpeed(Wheel * wheel);
float wheel_tangentialSpeed(Wheel * wheel);
void wheel_setSpeedPercent(Wheel * wheel, float speed);
#endif// WHEEL_H
