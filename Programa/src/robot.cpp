#include "robot.h"

Robot::Robot(PowerTrain * train, Timer * timer, Button * button):
	train_{train}, timer_{timer}, button_{button}
{
}
void Robot::moveFordward(void)
{
	if(button_->pushed()){
		train_->on();
		timer_->enable();
		if(timer_->getTime() >= 1000)
			train_->off();
	}
}
