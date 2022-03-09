#ifndef PID_H
#define PID_H
typedef struct Pid{
	float sp;
	float kp;
	float ki;
	float error;
	float last_error;
	float integral;
}Pid;

Pid pid_create(void);
void pid_setSp(Pid * pid, float sp);
void pid_setKp(Pid * pid, float kp);
void pid_setKi(Pid * pid, float ki);
float pid_do(Pid * pid, float pv);
#endif// PID_H
