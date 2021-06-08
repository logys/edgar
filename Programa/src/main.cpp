#include "mobile_robot.h"
#include "motorDc.h"
#include "differential.h"
#include "timer_delay.h"
#include "robotController.h"
#include "bluetooth.h"
#include "serial.h"

int main(void)
{
	MotorDc left(10, 1, 2);
	MotorDc right(9, 23, 24);
	Differential train(&left, &right);
	Timer_delay timer;
	MobileRobot robot(&train, &timer);
	RobotController controller(&robot);
	Bluetooth ble(&controller);
	serial_init(&ble);

	while(1){
		if(serial_dataNew()){
			auto data = serial_read();
			serial_asyncCall(data);
		}
	}
	return 0;
}
