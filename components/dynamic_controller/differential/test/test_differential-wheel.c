#include "unity.c"
#include "differential.h"
#include "wheel.h"
#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(float, encoder_speed, Encoder *);
FAKE_VOID_FUNC(motor_setWC, Motor *, float);

void setUp(void)
{
}
