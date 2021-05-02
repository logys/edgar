#include "robot.h"

Robot::Robot(PowerTrain * train, Timer * timer):
	train_{train}, timer_{timer}
{
}
void Robot::moveForward(void)
{
	train_->forward();
	timer_->enable();
	while(timer_->getTime() < 1000);
	train_->off();
}
void Robot::moveBackward(void)
{
	train_->backward();
	timer_->enable();
	while(timer_->getTime() < 1000);
	train_->off();
}
