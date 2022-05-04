#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "point.h"
#include "speeds.h"

typedef struct PositionErrors{
	float dx, dy, dphi;
}PositionErrors;

typedef struct Position{
	float x, y, phi;
}Position;

void controller_setPoint(Point point);
Point controller_getReferencePoint(void);
PositionErrors controller_getErrors(void);
Speeds controller_do(void);
Position controller_updatePosition(Speeds speeds);
#endif// CONTROLLER_H
