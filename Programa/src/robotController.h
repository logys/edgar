#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H 

#include "command_selector.h"
#include "robot.h"

class RobotController : public CommandSelector{
	private:
		Robot * robot_;
	public:
		RobotController(Robot *);
		void sendMovement(Direction direction) override;
};

#endif //ROBOTCONTROLLER_H
