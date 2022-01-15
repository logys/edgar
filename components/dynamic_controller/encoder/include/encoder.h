#ifndef ENCODER_H
#define ENCODER_H

#include "tick_counter.h"
#include <stdint.h>

typedef struct Encoder{
	TickCounter * tick;
	int16_t REV_TICKS;
	float time;
}Encoder;

Encoder encoder_create(TickCounter * tick, int16_t rev_ticks, float time);
float encoder_speed(Encoder * encoder);

#endif// ENCODER_H
