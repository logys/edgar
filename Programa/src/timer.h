#ifndef TIMER_H
#define TIMER_H
class Timer{
	public:
		virtual void enable(void) = 0;
		virtual unsigned long getTime(void) = 0;
};
#endif // TIMER_H
