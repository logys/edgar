#include "robot.h"
#include "timer.h"
#include "button.h"
#include "motor.h"
#include "motor_single.h"
#include "timer_delay.h"
#include "push.h"


int main(void)
{
	Single_motor motor(1);
	Timer_delay timer;
	Push push(2);
	Robot robot(&motor,&timer, &push);

	while(1){
		robot.moveFordward();
	}

	return 0;
}
