#include "motorDc.h"
#include "gpio.h"

MotorDc::MotorDc(short const pin) : pin_{pin}
{
	gpio_setDirection(pin_, OUTPUT);
}
void MotorDc::on(void)
{
	gpio_setLevel(pin_, HIGH);
}
void MotorDc::off(void)
{
	gpio_setLevel(pin_, LOW);
}
