#include "pid.h"

Pid pid_create(void)
{
	return (Pid){};
}

void pid_setSp(Pid * pid, float sp)
{
	pid->sp = sp;
}

void pid_setKp(Pid * pid, float kp)
{
	pid->kp = kp;
}

void pid_setKi(Pid * pid, float ki)
{
	pid->ki = ki;
}

float pid_do(Pid * pid, float pv)
{
	pid->error = pid->sp - pv;
	pid->integral += pid->error*0.1;
	float result = pid->kp*pid->error + pid->ki*pid->integral;
	pid->last_error = pid->error;
	return result;
}
