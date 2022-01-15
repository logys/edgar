#include "tick_counter.h"
#include "driver/pcnt.h"
#include <stdint.h>

int16_t counter_value;
int16_t tickCounter_ticks(TickCounter * tick)
{
	pcnt_get_counter_value(tick->unit, &counter_value);
	pcnt_counter_clear(tick->unit);
	return counter_value;
}

TickCounter tickCounter_create(pcnt_unit_t unit, uint8_t phase_A, uint8_t phase_B)
{
	pcnt_config_t config = {
		.pulse_gpio_num = phase_A,
		.ctrl_gpio_num = phase_B,
		.lctrl_mode = PCNT_MODE_KEEP,
		.hctrl_mode = PCNT_MODE_REVERSE,
		.counter_h_lim = 2000,
		.counter_l_lim = -2000,
		.pos_mode = PCNT_COUNT_INC,
		.neg_mode = PCNT_COUNT_DIS,
		.unit = unit,
		.channel = PCNT_CHANNEL_0
	};
	pcnt_unit_config(&config);
	pcnt_counter_pause(unit);
	pcnt_counter_clear(unit);
	pcnt_counter_resume(unit);
	TickCounter tmp = {
		.unit = unit
	};
	return tmp;
}
