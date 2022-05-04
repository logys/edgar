#include "controller.h"
#include <math.h>

static Point reference_point_ = {};
Position current_position_ = {};
PositionErrors errors_ = {};
float phi_ref = 0;
static Speeds speeds_ = {};

static void compute_errors(void);

void controller_setPoint(Point point)
{
	reference_point_.x = point.x;
	reference_point_.y = point.y;
}

Point controller_getReferencePoint(void)
{
	return reference_point_;
}

PositionErrors controller_getErrors(void)
{
	return errors_;
}

static void compute_errors(void)
{
	errors_.dx = reference_point_.x - current_position_.x;
	errors_.dy = reference_point_.y - current_position_.y;
	phi_ref = atan2(errors_.dy, errors_.dx);
	errors_.dphi = phi_ref - current_position_.phi;
}

#define KLIN 1
#define KANG 1
#define TS 0.1

static void compute_speeds(void);

Speeds controller_do(void)
{
	compute_errors();
	compute_speeds();
	return speeds_;
}

static void compute_speeds(void)
{
	speeds_.linear = KLIN * 
		sqrt(pow(errors_.dx, 2) + pow(errors_.dy, 2));
	speeds_.angular = KANG * errors_.dphi;
}

Position controller_updatePosition(Speeds speeds)
{
	current_position_.x = TS * speeds.linear * cos(current_position_.phi);
	current_position_.y = TS * speeds.linear * sin(current_position_.phi);
	current_position_.phi = TS * speeds.angular/20.0*tan(errors_.dphi);
	return current_position_;
}
