#ifndef COMMAND_SELECTOR_H
#define COMMAND_SELECTOR_H
#include "direction.h"

class CommandSelector{
	public:
		virtual void sendMovement(Direction direction) = 0;
};
#endif //COMMUNICATIONDRIVER_H
