#ifndef MOBILE_ROBOT_H
#define MOBILE_ROBOT_H

#include "power_train.h"
#include "timer.h"
#include "robot.h"

class MobileRobot : public Robot{
	private:
		PowerTrain * train_;
		Timer * timer_;
	public:
		MobileRobot(PowerTrain *, Timer *);
		void moveForward(void) override;
		void moveBackward(void) override;
};
#endif // MOBILE_ROBOT_H
