#include "robot.h"

Robot::Robot(Motor * motor, Timer * timer, Button * button):
	motor_{motor}, timer_{timer}, button_{button}
{
}
void Robot::moveFordward(void)
{
	if(button_->pushed()){
		motor_->on();
		timer_->enable();
		if(timer_->getTime() >= 1000)
			motor_->off();
	}
}
