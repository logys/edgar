#ifndef ROBOT_H
#define ROBOT_H

#include "power_train.h"
#include "timer.h"
#include "button.h"

class Robot{
	private:
		Button * button_;
		PowerTrain * train_;
		Timer * timer_;
	public:
		Robot(PowerTrain *, Timer *, Button *);
		void moveFordward(void);
};
#endif // ROBOT_H
