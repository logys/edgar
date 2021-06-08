#ifndef BLUETOOTH_H
#define BLUETOOTH_H 
#include "communication_driver.h"
#include "command_selector.h"
#include "direction.h"

class Bluetooth : public CommunicationDriver{
	private:
		Direction direction;
		CommandSelector * command_selector_;
	public:
		Bluetooth(CommandSelector * command_selector);
		void sendUserInput(short data) override;
};
#endif //BLUETOOTH_H
