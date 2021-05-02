#ifndef PWM_H
#define PWM_H

void pwm_enablePin(short const pin);
void pwm_disablePin(short const pin);
void pwm_enableTimer(void);
void pwm_disableTimer(void);
void pwm_setWorkCycle(short const pin, short wc);

#endif// PWM_H
