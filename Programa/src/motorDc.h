#ifndef MOTORDC_H
#define MOTORDC_H

#include "motor.h"

class MotorDc : public Motor{
	private:
		short pin_;
	public:
		MotorDc(short const pin);
		virtual void on(void) override;
		virtual void off(void) override;
};
#endif// MOTORDC_H
