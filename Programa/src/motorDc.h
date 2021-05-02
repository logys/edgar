#ifndef MOTORDC_H
#define MOTORDC_H

#include "motor.h"
#include "pwm.h"

class MotorDc : public Motor{
	private:
		short pin_enable_;
		short pin_input1_;
		short pin_input2_;
	public:
		MotorDc(short const pin_enable, short const pin_input1,
			       	short const pin_input2);
		virtual void forward(short const power) override;
		virtual void backward(short const power) override;
		virtual void off(void) override;
};
#endif// MOTORDC_H
