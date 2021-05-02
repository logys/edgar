#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#include "power_train.h"
#include "motor.h"

class Differential : public PowerTrain{
	private:
		Motor *left_;
		Motor *rigth_;
	public:
		Differential(Motor *, Motor *);
		virtual void forward(void) override;
		virtual void backward(void) override;
		virtual void off(void) override;
};

#endif// DIFFERENTIAL_H
