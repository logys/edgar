#include "pwm.h"
#include "driver/mcpwm.h"
//#include "esp_log.h"
//static char const * tag = "pwm wc";

void pwm_setWC(Pwm * pwm, float wc)
{
	//ESP_LOGI(tag, "timer: %d, wc: %0.4f",pwm->timer, wc);
	if(wc == 0){
		mcpwm_set_signal_low(MCPWM_UNIT_0, pwm->timer, pwm->generator);
	}
	mcpwm_set_duty(MCPWM_UNIT_0, pwm->timer, pwm->generator, wc);
	mcpwm_set_duty_type(MCPWM_UNIT_0, pwm->timer, pwm->generator, MCPWM_DUTY_MODE_0);
}

Pwm pwm_create(mcpwm_io_signals_t signal, uint16_t frequency, int8_t pin)
{
	mcpwm_gpio_init(MCPWM_UNIT_0, signal, pin);
	mcpwm_timer_t timer;
	mcpwm_generator_t generator;
	if(signal == MCPWM0A){
		timer = MCPWM_TIMER_0;
		generator = MCPWM_GEN_A;
	}else if(signal == MCPWM0B){
		timer = MCPWM_TIMER_0;
		generator = MCPWM_GEN_B;
	}else if(signal == MCPWM1A){
		timer = MCPWM_TIMER_1;
		generator = MCPWM_GEN_A;
	}else{
		timer = MCPWM_TIMER_1;
		generator = MCPWM_GEN_B;
	}
	mcpwm_config_t config = {
		.frequency = frequency,
		.cmpr_a = 0,
		.cmpr_b = 0,
		.duty_mode = MCPWM_DUTY_MODE_0,
		.counter_mode = MCPWM_UP_COUNTER
	};
	mcpwm_init(MCPWM_UNIT_0, timer, &config);
	return (Pwm){
		.timer = timer, 
		.generator = generator
       };
}
