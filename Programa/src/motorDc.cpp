#include "motorDc.h"
#include "gpio.h"
#include "pwm.h"

MotorDc::MotorDc(short const pin_enable, short const pin_input1, short const pin_input2) :
       	pin_enable_{pin_enable}, pin_input1_{pin_input1}, pin_input2_{pin_input2}
{
	gpio_setDirection(pin_enable_, OUTPUT);
	gpio_setDirection(pin_input1_, OUTPUT);
	gpio_setDirection(pin_input2_, OUTPUT);
	pwm_enableTimer();
}

void MotorDc::forward(short const power)
{
	gpio_setLevel(pin_input1_, HIGH);
	gpio_setLevel(pin_input2_, LOW);
	pwm_setWorkCycle(pin_enable_, power);
	pwm_enablePin(pin_enable_);
}

void MotorDc::backward(short const power)
{
	gpio_setLevel(pin_input1_, LOW);
	gpio_setLevel(pin_input2_, HIGH);
	pwm_setWorkCycle(pin_enable_, power);
	pwm_enablePin(pin_enable_);
}

void MotorDc::off(void)
{
	gpio_setLevel(pin_input1_, LOW);
	gpio_setLevel(pin_input2_, LOW);
	pwm_disablePin(pin_enable_);
}
