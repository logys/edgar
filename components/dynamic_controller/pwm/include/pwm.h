#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include "driver/mcpwm.h"

typedef struct Pwm{
	uint8_t timer;
	uint8_t generator;
}Pwm;

Pwm pwm_create(mcpwm_io_signals_t signal, uint16_t frequency, int8_t pin);
void pwm_setWC(Pwm * pwm, float wc);

#endif// PWM_H
