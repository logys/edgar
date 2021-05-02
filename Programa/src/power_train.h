#ifndef POWER_TRAIN_H
#define POWER_TRAIN_H
class PowerTrain{
	public: 
		virtual void forward(void) = 0;
		virtual void backward(void) = 0;
		virtual void off(void) = 0;
};
#endif// POWER_TRAIN_H
