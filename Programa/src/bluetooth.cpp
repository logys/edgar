#include "bluetooth.h"

Bluetooth::Bluetooth(CommandSelector * command_selector) :
       	command_selector_{command_selector}
{
}

void Bluetooth::sendUserInput(short data)
{
	if(data == '0')
		command_selector_->sendMovement(Direction::FORWARD);
	else if(data == '1')
		command_selector_->sendMovement(Direction::BACKWARD);
}
