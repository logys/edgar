#ifndef ROBOT_H
#define ROBOT_H

#include "motor.h"
#include "timer.h"
#include "button.h"

class Robot{
	private:
		Button * button_;
		Motor * motor_;
		Timer * timer_;
	public:
		Robot(Motor *, Timer *, Button *);
		void moveFordward(void);
};
#endif // ROBOT_H
