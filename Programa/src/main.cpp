#include "robot.h"
#include "motorDc.h"
#include "differential.h"
#include "timer_delay.h"
#include "push.h"


int main(void)
{
	MotorDc left(10, 1, 2);
	MotorDc right(9, 23, 24);
	Differential train(&left, &right);
	Timer_delay timer;
	Robot robot(&train, &timer);
	Push push(32);

	while(1){
		if(push.pushed()){
			robot.moveForward();
			robot.moveBackward();
		}
	}
	return 0;
}
