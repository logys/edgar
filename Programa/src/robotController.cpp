#include "robotController.h"

RobotController::RobotController(Robot * robot) :
	robot_{robot}
{
}

void RobotController::sendMovement(Direction direction)
{
	if(direction == Direction::FORWARD)
		robot_->moveForward();
	else if(direction == Direction::BACKWARD)
		robot_->moveBackward();
}
