#ifndef POINT_CONTROLLER_H
#define POINT_CONTROLLER_H

#include "point.h"
#include "speeds.h"

void pointController_init(void);
void pointController_start(void);
void pointController_stop(void);
void pointController_setPoint(Point point);
void pointController_setSpeeds(Speeds speeds);


#endif// POINT_CONTROLLER_H
