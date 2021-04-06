#ifndef MOTOR_H
#define MOTOR_H
class Motor{
	public: 
		virtual void on(void) = 0;
		virtual void off(void) = 0;
};
#endif// MOTOR_H
