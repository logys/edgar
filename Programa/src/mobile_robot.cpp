#include "mobile_robot.h"

MobileRobot::MobileRobot(PowerTrain * train, Timer * timer):
	train_{train}, timer_{timer}
{
}
void MobileRobot::moveForward(void)
{
	train_->forward();
	timer_->enable();
	while(timer_->getTime() < 1000);
	train_->off();
}
void MobileRobot::moveBackward(void)
{
	train_->backward();
	timer_->enable();
	while(timer_->getTime() < 1000);
	train_->off();
}
