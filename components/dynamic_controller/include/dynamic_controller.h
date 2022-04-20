#ifndef DYNAMIC_CONTROLLER_H
#define DYNAMIC_CONTROLLER_H

#include <stdint.h>
#include "speeds.h"

void dynamicController_init(void);
void dynamicController_start(void);
void dynamicController_stop(void);
void dynamicController_setSpeeds(Speeds speeds);
void dynamicController_setKp(uint8_t number, float kp);
void dynamicController_setKi(uint8_t number, float ki);

#endif// DYNAMIC_CONTROLLER_H
