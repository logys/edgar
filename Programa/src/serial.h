#ifndef SERIAL_H 
#define SERIAL_H 

#include "communication_driver.h"

void serial_init(CommunicationDriver * driver);
short serial_read(void);
bool serial_dataNew(void);
void serial_asyncCall(short data);

#endif //SERIAL_H
