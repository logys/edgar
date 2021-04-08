#include "differential.h"
Differential::Differential(Motor * left, Motor * right) : rigth_{right}, left_{left}
{
}
void Differential::on(void)
{
	rigth_->on();
	left_->on();
}
void Differential::off(void)
{
	rigth_->off();
	left_->off();
}
