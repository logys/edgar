#ifndef ROBOT_H
#define ROBOT_H

#include "power_train.h"
#include "timer.h"

class Robot{
	private:
		PowerTrain * train_;
		Timer * timer_;
	public:
		Robot(PowerTrain *, Timer *);
		void moveForward(void);
		void moveBackward(void);
};
#endif // ROBOT_H
