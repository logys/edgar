/*
 * =====================================================================================
 *
 *       Filename:  stub_sleep.h
 *
 *    Description:  stub for sleep
 *
 *        Version:  1.0
 *        Created:  09/02/20 00:39:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luis Antonio Sánchez Monterde (logy), antonio.dgr.ink@gmail.com
 *   Organization:  eleckia
 *
 * =====================================================================================
 */
#ifndef STUB_INTERRUPT_H
#define STUB_INTERRUPT_H

#include<stdint.h>

#define ISR(interrupt) void interrupt(void)

ISR(TIM1_COMPA_vect);
ISR(PCINT0_vect);

#endif
