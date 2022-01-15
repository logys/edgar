#ifndef DYNAMIC_CONTROLLER_H
#define DYNAMIC_CONTROLLER_H

void dynamicController_init(void);
void dynamicController_setSpeeds(float linear, float angular);
void dynamicController_setLinear(float speed);
void dynamicController_setAngular(float speed);
void dynamicController_start(void);
void dynamicController_stop(void);

#endif// DYNAMIC_CONTROLLER_H
