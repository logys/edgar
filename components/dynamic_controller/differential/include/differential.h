#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#include "wheel.h"

void differential_setSpeeds(float lineal, float angular);
void differential_setLinearSpeed(float speed);
void differential_setAngularSpeed(float speed);
void differential_init(Wheel * left, Wheel *right);
void differential_do(void);
void differential_stop(void);
float differential_linearSpeed(void);
float differential_angularSpeed(void);

#endif// DIFFERENTIAL_H
