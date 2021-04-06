#ifndef TIMER_DELAY_H
#define TIMER_DELAY_H

#include "timer.h"

class Timer_delay : public Timer
{
	virtual void enable(void) override;
	virtual unsigned long getTime(void) override;
};

#endif// TIMER_DELAY_H
