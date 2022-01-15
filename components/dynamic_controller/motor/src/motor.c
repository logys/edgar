#include "motor.h"
#include "pwm.h"
//#include "esp_log.h"
//static char * tag = "motor";

#define WIDE_HYSTERESIS 10

void motor_setWC(Motor * motor, float wc)
{
//	ESP_LOGI(tag, "motor wc: %0.4f", wc);
	if(wc > WIDE_HYSTERESIS){
		pwm_setWC(motor->pwmIn1, wc);
		pwm_setWC(motor->pwmIn2, 0);
	}else if(wc < -1*WIDE_HYSTERESIS){
		pwm_setWC(motor->pwmIn1, 0);
		pwm_setWC(motor->pwmIn2, -1*wc);
	}else{
		motor_stop(motor);
	}
}

void motor_stop(Motor * motor)
{
	pwm_setWC(motor->pwmIn1, 0);
	pwm_setWC(motor->pwmIn2, 0);
}

Motor motor_create(Pwm * pwmIn1, Pwm * pwmIn2)
{
	Motor motor = {
		.pwmIn1 = pwmIn1,
		.pwmIn2 = pwmIn2
	};
	return motor;
}
