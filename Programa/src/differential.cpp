#include "differential.h"
Differential::Differential(Motor * left, Motor * right) :
       	rigth_{right}, left_{left}
{
}

void Differential::forward(void)
{
	left_->forward(97);
	rigth_->backward(100);
}

void Differential::backward(void)
{
	left_->backward(97);
	rigth_->forward(100);
}

void Differential::off(void)
{
	rigth_->off();
	left_->off();
}
