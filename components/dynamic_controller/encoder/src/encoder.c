#include "encoder.h"
#include "tick_counter.h"

float encoder_speed(Encoder * encoder)
{
	return tickCounter_ticks(encoder->tick) / (float)encoder->REV_TICKS / encoder->time;
}

Encoder encoder_create(TickCounter * tick_, int16_t rev_ticks_, float time_)
{	
	Encoder tmp = {
		.tick = tick_,
		.REV_TICKS = rev_ticks_,
		.time = time_
	};
	return tmp;
}
