#include "robot.h"
#include "motorDc.h"
#include "differential.h"
#include "timer_delay.h"
#include "push.h"


int main(void)
{
	MotorDc left(1);
	MotorDc right(2);
	Differential train(&left, &right);
	Timer_delay timer;
	Push push(2);
	Robot robot(&train, &timer, &push);

	while(1){
		robot.moveFordward();
	}

	return 0;
}
