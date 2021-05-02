#include "timer_delay.h"
#include <util/delay.h>

void Timer_delay::enable(void)
{
}
unsigned long Timer_delay::getTime(void)
{
	_delay_ms(2000);
	return 1000;
}
