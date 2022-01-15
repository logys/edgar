#ifndef TICK_COUNTER
#define TICK_COUNTER

#include <stdint.h>
#include "driver/pcnt.h"

typedef struct TickCounter{
	pcnt_unit_t unit;
}TickCounter;

TickCounter tickCounter_create(pcnt_unit_t unit, uint8_t phase_A, uint8_t phase_B);
int16_t tickCounter_ticks(TickCounter * tick);

#endif// TICK_COUNTER
