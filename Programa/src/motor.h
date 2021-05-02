#ifndef MOTOR_H
#define MOTOR_H
class Motor{
	public: 
		virtual void forward(short const power) = 0;
		virtual void backward(short const power) = 0;
		virtual void off(void) = 0;
};
#endif// MOTOR_H
