#include "wheel.h"
#include "encoder.h"
#include "motor.h"

Wheel wheel_create(Motor * motor, Encoder * encoder, float rad)
{
	return (Wheel){.motor = motor,
		.encoder = encoder,
		.rad = rad
	};
}

float wheel_angularSpeed(Wheel * wheel)
{
	return encoder_speed(wheel->encoder);
}

float wheel_tangentialSpeed(Wheel * wheel)
{
	return wheel->rad * encoder_speed(wheel->encoder);
}

void wheel_setSpeedPercent(Wheel * wheel, float speed)
{
	motor_setWC(wheel->motor, speed);
}
